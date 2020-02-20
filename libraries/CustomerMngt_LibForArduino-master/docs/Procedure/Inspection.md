# 概要

こちらの[スケッチ](../../library/examples/Inspection/Inspection.ino)を、検査対象基板に書込むスケッチに付け足す。

[CustomerMngt_LibForArduino](https://github.com/cami/CustomerMngt_LibForArduino)を適切な階層に配置する必要がある（詳しくは、README.mdを読むこと）。

`SORACOM Funnel`を介して、`AWS IoT Core`にアクセスして、DynamoDBに基板情報を保存する。

SORACOM上では、`基板検査`というグループを作り、そこに`AWS IoT Core`のIAMユーザーの権限を付与して、`SORACOM Funnel`を利用している。

 
## Include文

次の1行を加える。

```
#include "NectisCustomerMngt.h"   // For Customer Management
```


## インスタンスの作成

次の1行を加える。

```
CustomerManagement Mngt;    // For Customer Management

```


## LTE-M経由で基板情報の送信

setup()関数の末尾に、次の1行を加える。

```
  Serial.println("Inspection()");    // For Inspection
  Mngt.Inspection();    // For Inspection
```


## DynamoDBへの基板情報の登録

[inspection_dynamodb](../png/inspection_dynamodb.png)

