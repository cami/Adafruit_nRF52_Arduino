# Policy for Customer Management

* 顧客管理の方針
 
基板検査時・プロビジョニング時・利用開始時・請求書発行時等に、

必要に応じて`AWS Lambda`を介して、`SORACOM API`・`Money Forward API`を叩くことで、

`DynamoDB`をデータベースとして使用した手軽に顧客管理を実現する。

* 目次

| 目次 | リンク |
| :--- | :--- |
| 基板検査 | [#基板検査](https://github.com/cami/CustomerMngt_LibForArduino/blob/feature/implement/CustomerMngt-Policy.md#%E5%9F%BA%E6%9D%BF%E6%A4%9C%E6%9F%BB) |
| 契約 | [#契約](https://github.com/cami/CustomerMngt_LibForArduino/blob/feature/implement/CustomerMngt-Policy.md#%E5%A5%91%E7%B4%84) |
| 利用開始 | [#利用開始](https://github.com/cami/CustomerMngt_LibForArduino/blob/feature/implement/CustomerMngt-Policy.md#%E5%88%A9%E7%94%A8%E9%96%8B%E5%A7%8B) |
| Lagoon管理 | [#Lagoon管理](https://github.com/cami/CustomerMngt_LibForArduino/blob/feature/implement/CustomerMngt-Policy.md#lagoon%E7%AE%A1%E7%90%86) |
| OTA-DFU(LTE-M)管理 | [#OTA-DFU(LTE-M)管理](https://github.com/cami/CustomerMngt_LibForArduino/blob/feature/implement/CustomerMngt-Policy.md#ota-dfulte-m%E7%AE%A1%E7%90%86) |
| 請求書発行 | [#請求書発行](https://github.com/cami/CustomerMngt_LibForArduino/blob/feature/implement/CustomerMngt-Policy.md#%E8%AB%8B%E6%B1%82%E6%9B%B8%E7%99%BA%E8%A1%8C) |
| 解約 | [#解約](https://github.com/cami/CustomerMngt_LibForArduino/blob/feature/implement/CustomerMngt-Policy.md#%E8%A7%A3%E7%B4%84) |

`imei`=> 基板を一意に管理

`group_id`=> お客様を一意に管理

`imsi`と`group_id`を一意に紐づけるのが、`imsi`。
 
 コンソールを使用中に発生したエラーログは、下記リポジトリに保存されている。
 
[log](./log/soracom_funnel-to-aws_dynamo_db.log)


* AWSのIAMユーザー

SORACOM Funnel=> IoT_PF-SORACOM-Customer_Mngt

Console(Python)=> IoT_PF-console-Customer_Mngt

* Note: `Rule query statement` for AWS IoT should be the following.

```
SELECT payloads.*, parse_time("yyyy.MM.dd HH:mm:ss", timestamp(), "Asia/Tokyo") as timestamp FROM 'customer_mngt'
```

Do NOT forget the `'` for the `topic`.


## 顧客を一意に管理するキー

1. imei (BG96)


2. group_id

SORACOMのGroupごとに顧客を管理する。

Groupは契約者ごとに発行される。

例えば、同じ会社の中の異なる部署と契約した場合には、会社名に部署名も含める。

`契約情報`を入力して、SIMを発注した段階でGroupを作成できる。

* imsi

基板と顧客情報を紐づけるために、`imsi`を使用する。


## データベース

データベースは2つ使用する。

| # | 用途 | テーブル名 | 利用サービス |
| :---: | :--- | :---: | :--- |
| 0 | 利用状況データベース | Customer_Management | AWS DynamoDB |
| 1 | 顧客情報管理データベース | Customer_Info | AWS RDB |

基板情報と契約者のgroup_idを管理するデータベース（DynamoDB）と、

顧客情報のみを管理するデータベース（RDB）である。


## SIM利用状況フラグ

`sim_status`として管理する。

SORACOMのSIMのステータスに合わせる


## 基板管理フラグ

`board_status`として管理する。
 
| フラグ | 利用状況 | タイミング |
| :---: | :---: | :--- |
| 0 | 在庫 | 基板検査終了時に、基板から |
| 1 | 契約完了 | 契約情報登録時に、コンソールから |
| 2 | 出荷準備完了 | 基板とSIMの組立て完了時に、AWS Lambdaから |
| 3 | 利用開始 | SORACOM Harvest Dataへの初回通信時に、AWS Lambdaから |
| 4 | 解約済み | 契約解除時に、コンソールから |

基板検査が終了すると同時に、在庫として扱う。

会社つまりgroup_id相当、会社名、請求先住所、氏名、メール、年月、金額、何の契約、請求方法、請求ステータス、支払ステータス


ヤマト運輸のAPIを叩くためには、有料プランを契約する必要があるため、基板の出荷準備が整うと、`group_id`を元に送り先を取得する。

取得した送り先は、Lambdaを介して、送り先、基板の個数、契約プランを、Slackに送る。

請求書をGoogleDriveに保存する際は、`iot_dx_money_fwd@cami.jp`アカウントを使用する。


## SAMユーザー

SORACOMのSAMユーザーとして、下記のものを想定している。

| ユーザー名 | 権限 |
| :--- | :--- |
| 契約情報登録ユーザー | 顧客情報を登録して、SIMを発注できる |
| Lagoonアカウント発行ユーザー | Lagoonアカウントを新規発行できる |
| OTA-DFU管理ユーザー | .bin形式でファームウェアをHardvest Filesにアップロードできる |
| 請求書発行ユーザー | 必要があれば、請求書をCSVでダウンロードすることができる |
| SIM解約ユーザー | SIMの解約手続きを行える |


## 基板検査

検査に合格すれば、`在庫`フラグを立て、同時に`imei`を送信する。


### スケッチ

[Inspection.ino](../../library/examples/Inspection/Inspection.ino)

このスケッチを検査用のスケッチとマージする。

検査用のSIMは、 `"imsi":"440525060010923"`


### AWS Lambda

`imei`,`STATUS`がAWS IoTを介して、AWS Lambdaに送信される。
 
`Dynamo DB`に通知が行く。

`SORACOM API`には何もしない。


### Dynamo DB

`imei`と状況に応じた`STATUS`が投入される。

`trouble`の有無（お客さんの手に渡ってからも）も記録したい?
 
 
### SORACOM API

なし。


### Money Forward API

なし。


### ヤマト運輸

なし。


## 契約

お客様から、以下の契約情報を受け取る。

```
会社名
連絡先メールアドレス
契約プラン（書き込むスケッチを特定するため）
発送先住所
契約開始日（契約期間）
支払い方法（現在は、請求書払いのみ対応）
```

`契約情報`はSORACOM上でGroupを作成することで、会社ごとに`group_id`で管理される。

契約情報を入力（入力先はコンソール）すると、AWS Lambdaにリクエストが飛び、`契約完了`フラグが立つ。

Dynamo DBに`契約情報`と`group_id`が保存され、SORACOM APIを介して、SIMが発注される（このタイミングでimsiが確定する）。

SIMが到着すると、API経由で`受取済み`のステータスに変更し、Dynamo DBの契約情報に`imsi`を追加する。

同時に、契約プランに応じたスケッチを基板に書き込む。

SIMが到着すると、契約プランに応じた発注するSIM・基板・アンテナ等をセットにして、Bootloaderとスケッチを書き込む。

書き込み後、電源を投入して、1度目のLTE-M通信の完了を確認してから、出荷する。（`出荷準備完了`フラグを立てるため。）


### コンソール 

`契約情報`を入力する。（SORACOM APIが自動で叩かれ、`group_id`がレスポンスとして帰ってくる）

入力方法は、 [README](../Procedure/Register.md) を参考にしてください。
 
SIMが到着したら、SORACOM API経由でSIMを受取済みにする。


### スケッチ

特になし。


### AWS Lambda

`契約情報`を受け取ると、Dynamo DBに`契約情報`が保存され、`SORACOM API`を介して、SIMが発注される。

SORACOM APIから、`group_id`がリスポンスとして帰ってくるので、DynamoDBに保存する。


### Dynamo DB

`契約完了`フラグが立ち、`契約情報`が保存される。

SIMの発注後、`group_id`が保存される。


### SORACOM API

`契約完了`が立つと、SIMが発注される。

SIMが到着後、SORACOMのステータスをコンソールから`SIM受取済み`に変更する。


### Money Forward API

なし。


### ヤマト運輸

`出荷準備完了`フラグが立つと、ヤマト運輸のAPIが叩かれ、発送先住所等が印刷される。

追跡番号を取得して、お客様に発想の完了と追跡番号をお知らせする。


## 利用開始

SIM・基板・センサの準備が整った段階で、動作確認テストを行う。

お客様の手元に商品が届き、電源が投入される。


### スケッチ

動作確認テストでは、納品用のスケッチに下記のマークダウンの必要な部分を追加して、初回通信確認を行う。

[Shipping](../Procedure/Shipping.md)

初回通信確認に合格すると、`利用開始`フラグが立つ。


### AWS Lambda

`出荷準備完了`フラグをスケッチから受け取ると、DynamoDBに`imsi`が追加される。


### Dynamo DB

初回LTE-M通信完了後に、`出荷準備完了`フラグが立ち`imsi`が保存される。

`利用開始`フラグを受け取り、ステータスを更新する。


### SORACOM API

指定した、１ヶ月あたりの通信料を超えると、Slackに通知を飛ばし、速度制限を行う。


### Money Forward API

なし。


### ヤマト運輸

なし。


## Lagoon管理

SORACOM Lagoonのアカウントが新規発行される。

お客様用のアカウントと、弊社管理用のアカウントがある。

お客様用のアカウントは`連絡先メールアドレス`を使用し、弊社監視用のアカウントは`会社名 + iot_dx_soracom@cami.jp`を使用する。


### スケッチ

なし。


### AWS Lambda

なし。


### Dynamo DB

なし。


### SORACOM API

API経由でLagoonを新規作成する。


### Money Forward API

なし。


### ヤマト運輸

なし。


## OTA-DFU(LTE-M)管理

お客様の要望をもとに、バージョンを`0.0.1`あげたスケッチを新規作成し、SORACOM Harvest Filesに配置する。

基板は1日間隔でOTA-DFUの有無を確認しており、自動で更新が適応される。

OTA-DFUの必要があれば、imeiに応じたgourp_idをlambdaがレスポンスとして戻す。
 
* Harvest Files上のファイル名の命名規則

ota/[group_id]/fw_[version].bin

ex.) CAMI&Co.の場合、`ota/OP0081185049/fw_0.0.1.bin`

更新が完了した基板の`sketch_ver`をDynamoDB上で更新する。


### スケッチ

バージョンを`0.0.1`あげたスケッチとなる。


### AWS Lambda

OTA-DFUの有無をimeiをもとに判断する。

imeiはgroup_idに紐づいており、OTA-DFUの有無は、Group単位で管理される。

もしあれば、スケッチの最新バージョンをレスポンスとして返し、DynamoDBのスケッチバージョンを更新する。


### Dynamo DB

DFUが完了すれば、`sketch_ver`を最新のものにアップデートする。
 

### SORACOM API

なし。


### Money Forward API

なし。


### ヤマト運輸

なし。


## 請求書発行

毎月、弊社で定めた日にちに請求書をSORACOMから取得して、MoneyForwardで請求書を作成したのちに、お客様に請求書を発行する。


### スケッチ

なし。


### AWS Lambda

日にちをトリガーとして、SORACOMの請求書発行のAPIを叩く。

SORACOMから請求書を受け取ると、利益を上乗せした金額で、MoneyForwardで請求書を作成する。

送付先のメールアドレス、もしくは住所とともに、GoogleDriveに請求書が保存される。


### Dynamo DB

AWS Lmabdaから要求されると、請求書の送付先のメールアドレス、もしくは住所を返す。


### SORACOM API

毎月決まった日にちになると、請求書発行のAPIが叩かれる。

請求金額をリスポンスとして返したい。


### Money Forward API

AWS Lambdaから、請求金額を受けとると、請求書が作成され、GoogleDriveに保存される。


### ヤマト運輸

なし。


## 解約

お客様から解約の要望を受けると、コンソールから解約手続きを行い、`解約済み`フラグを立てる。

基板の返却手続きが必要。


### スケッチ

なし。


### AWS Lambda

コンソールから、解約したいというリクエストを受ける。


### Dynamo DB

ステータスを`解約済み`に変更する。


### SORACOM API

APIを叩き、SIMを解約済みにする。


### Money Forward API

解約に伴う操作は、特になし。


### ヤマト運輸

なし。



