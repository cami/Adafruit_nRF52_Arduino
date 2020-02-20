# 概要

こちらの[スケッチ](../../library/examples/Shipping/Shipping.ino)を、検査対象基板に書込むスケッチに付け足す。

[CustomerMngt_LibForArduino](https://github.com/cami/CustomerMngt_LibForArduino)を適切な階層に配置する必要がある（詳しくは、README.mdを読むこと）。

`AWS API Gateway`経由で、`imsi`をキーとして、顧客情報を管理しているデータベースから受け取ってきた`group_id`を付与して、`DynamoDB`に基板情報を登録する。

 
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
  Serial.println("Shipping()");    // For Shipping
  Mngt.Shipping();    // For Shipping
```


## DynamoDBへの基板情報の登録

[shipping_merge_db](../png/shipping_merge_db.png)

