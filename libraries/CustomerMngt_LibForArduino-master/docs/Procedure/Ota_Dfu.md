# 概要

下記のようなOTA-DFUを実行する場合を考える。

| 旧 | 項目 | 新 |
| :--- | :---: | ---: |
| 環境測定 | 契約プラン | 環境測定 |
| cami | 契約者名 | cami |
| env_meas | スケッチ名 | env_meas |
| 0.0.1 | バージョン | 0.0.2 |

* "ファームウェア" = "スケッチの.bin" とする。


## SORACOM Harvest Filesのファイルパス

```
      sprintf(downloadFwUrl, "%s/ota/%s/fw_%s.%s", DOWNLOAD_FW_HOST, GROUP_ID, newestFwVer, filenameExtension);
```

スケッチでは、上記のようにURLを生成している。

`newestFwVer`は、OTA-DFUが必要であれば、AWS LambdaからのリスポンスのBodyに含まれている。

バージョンを`0.0.1`から`0.0.2`にあげる場合は、`"newestFwVer=0.0.2"`である。

今回は、

```
http://harvest-files.soracom.io/ota/OP0081185049/fw_0.0.2.bin
```

となり、一般的には、

```
http://harvest-files.soracom.io/ota/[GROUP_ID]/fw_[最新のスケッチバージョン].bin
```

となる。



## スケッチの変更点

```変更点なし 
#define DOWNLOAD_FW_HOST                "http://harvest-files.soracom.io"
#define GROUP_ID                        "OP0081185049"
 
 const char* filenameExtension = "bin";
```

```変更点あり
const char* firmwareVersion = "0.0.2";
```

それに加えて、ファームウェアの更新部分が、「変更点あり」となる。

動作確認を終えたら、ArduinoIDEを用いてコンパイルする。


## .binファイルの生成

今回は、例として、`LtemDfu.ino`を用いる。

[LtemDfu.ino](../png/LtemDfu.ino.png)

コンパイルが完了すると、ZIPファイルが生成されるので、そのパスをコピーする。

[zip_created_at](../png/zip_created_at.png)

今回は、下記の通りである。

`Zip created at /var/folders/nz/p2g5j75j15d1688n4f3c0wxr0000gp/T/arduino_build_327535/LtemDfu.ino.zip`

このZipファイルを解凍すると、`.bin`ファイルが含まれている。

これを、`OtaDfu_LibForArduino/SORACOM_Harvest_Files/ota/cami/`の配下に配置して解凍する。

```
$ mv /var/folders/nz/p2g5j75j15d1688n4f3c0wxr0000gp/T/arduino_build_327535/LtemDfu.ino.zip\
  [Your Path To]/OtaDfu_LibForArduino/SORACOM_Harvest_Files/ota/cami/

$ cd [Your Path To]/OtaDfu_LibForArduino/SORACOM_Harvest_Files/ota/cami/
$ unzip LtemDfu.ino.zip
```

Zipファイルを解凍した結果はこちら。

```
[Tachikoma@cami SORACOM_Harvest_Files] (feature/implement +)$
 unzip LtemDfu.ino.zip 
Archive:  LtemDfu.ino.zip
 extracting: manifest.json           
 extracting: LtemDfu.ino.bin         
 extracting: LtemDfu.ino.dat
```

最後に、ファイル名を変更する。

`mv LtemDfu.ino.bin fw_0.0.2.bin`


ここで、生成した`.bin`ファイルをSORACOM Harvest Filesに配置する。


## SORACOM Harvest Filesに配置

SORACOMコンソールにアクセスして、SORACOM Harvest Filesを開く。

[soracom_harvest_files](../png/soracom_harvest_files.png)

このように配置する。
 

## lambda_function.pyの更新

// ToDO: SORACOM Harvest Filesにファイルを配置したら、自動で`lambda_function.py`の`NEWEST_FW_VER = '0.0.1'`を更新したい。

[AWS lambda](https://ap-northeast-1.console.aws.amazon.com/lambda/home?region=ap-northeast-1#/functions/update_firmware_if_necessary?tab=graph)にアクセスする。

`lambda_function.py`の`NEWEST_FW_VER = '0.0.1'`を`NEWEST_FW_VER = '0.0.2'`に変更して、保存する。


## LTE-M 経由でのDFU

最長でも、1日に1度は、DFUの有無を問い合わせるようにスケッチを描いている。

DFUの状況は、[DynamoDB](https://ap-northeast-1.console.aws.amazon.com/dynamodb/home?region=ap-northeast-1#tables:selected=Customer_Management;tab=overview)で確認できる。

