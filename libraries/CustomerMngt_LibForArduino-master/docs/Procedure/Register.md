# 概要

```
会社名: 株式会社CAMI&Co.
部署: IoT 事業部
メールアドレス: iot_dx_soracom@cami.jp
契約プラン: 室内環境測定
請求先住所: 東京都品川区東五反田1-10-8 五反田S&Lビル8階
契約開始日: 2019-10-02
お支払い方法: 請求書
日別通信量制限: 1MiB
月別通信量制限: 3MiB
```

上記の顧客情報をデータベースに登録することを考える。

まずは、顧客情報をJSONファイルに記入する。

`.customers/customer_info`フォルダ内の`customers.json.example`をコピーして、`cami.json`とファイル名を変更する。

そのファイルを開くと、下記のような文字列が出てくる。

```
{
    "Company Name": "",                 # 契約した会社の正式名称
    "Department": "",                   # 契約した部署
    "Email Address": "",                # 連絡先となるメールアドレス
    "Plan": "",                         # 契約されたプラン名
    "Billing Address": "",              # 請求書の送付先住所
    "Contract Start Date": "",          # 契約開始日(ex. 2019-09-02)
    "Payment Method": "",               # お支払い方法(請求書払いのみ対応)
    "Daily Traffic Limit": "",          # 通信量制限（1日ごと、単位はMiB、下限は1MiB、デフォルトは1MiB）
    "Monthly Traffic Limit": ""         # 通信量制限（1ヶ月ごと、単位はMiB、下限は1MiB、デフォルトは3MiB）
}
```

英数字は半角で入力してください。

入力例はこちら。

```
{
    "Company Name": "株式会社CAMI&Co.",
    "Department": "IoT 事業部",
    "Email Address": "iot_dx_soracom@cami.jp",
    "Plan": "室内環境測定",
    "Billing Address": "東京都品川区東五反田1-10-8 五反田S&Lビル8階",
    "Contract Start Date": "2019-10-02",
    "Payment Method": "請求書",
    "Daily Traffic Limit": "1",
    "Monthly Traffic Limit": "3"
}
```

入力が完了すれば、保存する。


次に、コンソール画面からコマンドを叩き、データベースに登録していく。

// ToDO: 引数を取れるようにする。

`$ python3 main.py`

と実行すると、このような画面がでてくる。

<img src="../docs/png/main_sam_user.png" alt="main_sam_user" title="main_sam_user">

顧客登録の場合は、`0`を選択する。

<img src="../docs/png/main_input_json.png" alt="main_input_json" title="main_input_json">

`Enter the JSON file to singn up.(ex. cami):`と聞かれるので、先ほど作成したファイル名`cami`を入力する。

JSONファイルが存在すると、`Enter 'OK', if it is fine with you.`と確認を求められるので、`OK`と入力すれば、登録が完了する。


## DynamoDBへの基板情報の登録

### お客様情報を登録した段階

[register_dynamodb1](../png/register_dynamodb1.png)

[register_dynamodb2](../png/register_dynamodb2.png)

### SIMを受け取り処理を行った段階

[register_soracom](../png/register_soracom.png)

