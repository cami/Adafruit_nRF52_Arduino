# SORACOM API.

HTTP request and response body.


## /operators

```
curl -X POST \
  --header 'Content-Type: application/json' \
  --header 'Accept: application/json' \
  -d '{"email": "iot_dx_soracom@cami.jp", "password": "CAMI333cami"}' \
  'https://api.soracom.io/v1/operators'

no content
```

## /operators/verify

```
curl -X POST \
  --header 'Content-Type: application/json' \
  --header 'Accept: application/json' \
  -d '{"token": "ffdf4417-dab0-4b01-b8c8-9d2f79bba630-d5a5f042-5484-4a1c-8f32-19c7e8a78989"}' \
  'https://api.soracom.io/v1/operators/verify'

{
  "code": "COM0006",
  "message": "Token is invalid."
}
```


## /auth

```
curl -X POST \
  --header 'Content-Type: application/json' \
  --header 'Accept: application/json' \
  --header 'X-Soracom-API-Key: api-3904e648-dd53-447d-b2e9-927e320dcb8e' \
  --header 'X-Soracom-Token: eyJraWQiOiJBUUVDQUhnYmdGdnFrclRTbGlNVmNCQnV0VXlVcnNvU1RqTTM4NlR5WGVsaEdlUWtOd0FBQVk0d2dnR0tCZ2txaGtpRzl3MEJCd2FnZ2dGN01JSUJkd0lCQURDQ0FYQUdDU3FHU0liM0RRRUhBVEFlQmdsZ2hrZ0JaUU1FQVM0d0VRUU1uRWdLVlRiZGFsbWd4RGtkQWdFUWdJSUJRZlhXR1k1UHdqUjN4ZWY5SHhuZVo4NzN3THVHN3kzblY1TkZnTFZkNFdTaEdONTJBa1ZaVG55dG80RGY2UXVJWm9BS05KbFNqZWcyWnowRjV1S1p3amI0cy9pQlNCQno0bnZhcHdYQ0dOOFNjNHVMYVNKOUMzc2g3bmxFUFlSeTJRRHBCalhrL1BZNHpwbkYzQklRN3pQeXVKcmlqR0dwTmFDT3c3cXl2bGgwSXY0UVUzL0pmMFRWbUxteWlObEJLNVpMN25EV0JwZk1KUlJ5elVXZ2dxMUFYMXp1dndpV01KREZjMmVST0pOdkpxdXZ0TlR1M01sUm5RL29JOVBQWGNWdFhETFY3NEZMRVF3bWlmTUVhZVBxRzhvSjlQcnZmSlRMTnN1Q0xPYnMxVVI4dGU0eTJxS2xDQzFacVdYVitCWGM0WXROREhBbzNoN2xEbnVIOGRuUEozUjc0Z3dNcWE3L0dodjNUSWt1VlFmYzV0VDF4L25RR2pOdkZFVHZ2L1k3SWRsdkdsSU9BdE1UT09TRkRUWFNXZTVBN2I5T1pPU0Z4MTJZSjNxMHdnPT0iLCJhbGciOiJSUzI1NiJ9.eyJpc3MiOiJzb3JhY29tLmlvIiwiYXVkIjoiT3BlcmF0b3IiLCJleHAiOjE1NjgxMTYyMDEsImp0aSI6IkZJQkVxbWZObjYxenlFcElLaGt0RFEiLCJpYXQiOjE1NjgwMjk4MDEsIm5iZiI6MTU2ODAyOTY4MSwic3ViIjoic29yYWNvbSIsIm9wZXJhdG9yIjp7ImNvdmVyYWdlVHlwZXMiOlsianAiXSwicGVybWlzc2lvbnMiOlt7InN0YXRlbWVudHMiOlt7ImVmZmVjdCI6ImFsbG93IiwiYXBpIjpbIioiXX1dfV0sImFjY291bnRUeXBlIjoiMCIsInBheW1lbnRNZXRob2RTdGF0dXMiOiJyZWdpc3RlcmVkIiwib3BlcmF0b3JJZCI6Ik9QMDA4MTE4NTA0OSIsImNvdmVyYWdlVHlwZUF0dHJpYnV0ZXMiOnsianAiOnsidGVybXNWZXJzaW9uIjoiMSIsInBheW1lbnRNZXRob2RTdGF0dXMiOiJyZWdpc3RlcmVkIiwiY29udHJhY3RzIjpbXSwiY29udHJhY3REZXRhaWwiOnt9fX19fQ.nLcwz9CRR6z0vDFPSUUUTDtnWWFLjc3sJ2vo3Km3Yy3AGvPN9QvgV0WpgnHooF6ywtcdDnGONbSIBM1gUTNEeBD0FkXUETq-HUKF3UoVJuLlNjbrPFToBVMuP3fTSAkTxnBBxJb2qvAaaYFHANyvnjpdUqu--OJgCGuYx5HJZid-2y8AqYPZP6JZKSKQZ6w7ldlBnXQEdKAdYmYmLQnDfE5_IEhUZ1UPye9XCk-D6TWMmsDpRV-VgjfLeGvU6872ARBRzlpBbPAbUfx5OiShWBXcKhHyoOUFSVzLxpfWVK-_bLTejrXP9mAMGa7NjiXIsjQ-TXUED5xN9FqRR8hSlA' \
  -d '{
    "email": "iot_dx_soracom@cami.jp",
    "password": "CAMI333cami",
    "tokenTimeoutSeconds": 86400
  }' \
  'https://jp.api.soracom.io/v1/auth'

{
  "apiKey": "api-3904e648-dd53-447d-b2e9-927e320dcb8e",
  "operatorId": "OP0081185049",
  "token": "eyJraWQiOiJBUUVDQUhnYmdGdnFrclRTbGlNVmNCQnV0VXlVcnNvU1RqTTM4NlR5WGVsaEdlUWtOd0FBQVk0d2dnR0tCZ2txaGtpRzl3MEJCd2FnZ2dGN01JSUJkd0lCQURDQ0FYQUdDU3FHU0liM0RRRUhBVEFlQmdsZ2hrZ0JaUU1FQVM0d0VRUU0zMlNvRisyZUI4S3ZKME03QWdFUWdJSUJRZjAxQlVRenBYM21qUzdPcHU5dThnVXB6MVFKRzl2SklMSGxXaEZuRy9ITDZ5VXkyeHBoOWVBK1pnMEN3ZXVrVWtmZXJPSmVJVHlwbmlvWDlXaHgweW9MdlZXMm9CcnpVemZVU2dlOGlkaVJicUNTaVdMU1BUclNnaWZYamZTaEdxRXlVQ2V2bVhndGRWWjFsSTU1RzQ1WGsxN3dtTDNUalB1VHR6WXh2S0R1Q2M3OXlUbDEvZ3J6Y2pmc0t0Y21ZYm5JbTc4M1RPRUJObElFWTRDZ0NrYmJkRkdadGtFRHpJRFhGeXFKSGJQY3h6SHJIZzd0emg0Qk52UkNrdzJlRlVLYkczYm10VmhBdHhpblNUQm9HVllYYThKa0JVRXFCTk9XdE5oWk50NVN6VTdnMHBBbTd0QklhT2dxQlhFR2JrUWk5czFFRU1GVUIxRWRRU1kyOTkrUUt0ZUJMZUVYaGd0bzJ1OUNRajYxSWpWVGtMQTk2VGVIN0NOcWVBd3V5Z2Q4Z0dMdDdrbUFZTk1NWTMrQ3FtZlorVENZcm9xTDZjM0FRMzhJaS8xanNnPT0iLCJhbGciOiJSUzI1NiJ9.eyJpc3MiOiJzb3JhY29tLmlvIiwiYXVkIjoiT3BlcmF0b3IiLCJleHAiOjE1NjgxMTg2NzQsImp0aSI6InR6YzFwcnM0SlZGSkpqNENLMzVWbkEiLCJpYXQiOjE1NjgwMzIyNzQsIm5iZiI6MTU2ODAzMjE1NCwic3ViIjoic29yYWNvbSIsIm9wZXJhdG9yIjp7ImNvdmVyYWdlVHlwZXMiOlsianAiXSwicGVybWlzc2lvbnMiOlt7InN0YXRlbWVudHMiOlt7ImVmZmVjdCI6ImFsbG93IiwiYXBpIjpbIioiXX1dfV0sImFjY291bnRUeXBlIjoiMCIsInBheW1lbnRNZXRob2RTdGF0dXMiOiJyZWdpc3RlcmVkIiwib3BlcmF0b3JJZCI6Ik9QMDA4MTE4NTA0OSIsImNvdmVyYWdlVHlwZUF0dHJpYnV0ZXMiOnsianAiOnsidGVybXNWZXJzaW9uIjoiMSIsInBheW1lbnRNZXRob2RTdGF0dXMiOiJyZWdpc3RlcmVkIiwiY29udHJhY3RzIjpbXSwiY29udHJhY3REZXRhaWwiOnt9fX19fQ.V932RTJ9U3ppLIdxIinlvRp-Ox4OaFO-7-8f-HJ3-dxoe6eojBNRkkgxqBjm8kUk5C5CAjvPDKrvu3PgZDvjPQRdLgmJWyuhPVyFLhq3mfNHCOjt3LduS9XCa-hMp2AiuON_TQ74MrOzQj05QFzdkHsl5aiFZ2zdMk_VaUG10yx9lpzUb4OAZMmrC1BLAToL1cHJwJfrxfn7moSqEcpiFoXK_f_WLVn_ODHQgqlW2rQ20iaWdgK1u0reaJRBpkSiALfwM1H_BL0B--tB5jhXG86z6kgJXyd7cNO191QazKJfvFp5BRXESpaYqOM2LLYf2lPd9sec0rPNfdj2mMey7g"
}
```


## /payment_statements/payer_information

```
curl -X POST \
  --header 'Content-Type: application/json' \
  --header 'Accept: application/json;charset=UTF-8' \
  --header 'X-Soracom-API-Key: api-3904e648-dd53-447d-b2e9-927e320dcb8e' \
  --header 'X-Soracom-Token: eyJraWQiOiJBUUVDQUhnYmdGdnFrclRTbGlNVmNCQnV0VXlVcnNvU1RqTTM4NlR5WGVsaEdlUWtOd0FBQVk0d2dnR0tCZ2txaGtpRzl3MEJCd2FnZ2dGN01JSUJkd0lCQURDQ0FYQUdDU3FHU0liM0RRRUhBVEFlQmdsZ2hrZ0JaUU1FQVM0d0VRUU1uRWdLVlRiZGFsbWd4RGtkQWdFUWdJSUJRZlhXR1k1UHdqUjN4ZWY5SHhuZVo4NzN3THVHN3kzblY1TkZnTFZkNFdTaEdONTJBa1ZaVG55dG80RGY2UXVJWm9BS05KbFNqZWcyWnowRjV1S1p3amI0cy9pQlNCQno0bnZhcHdYQ0dOOFNjNHVMYVNKOUMzc2g3bmxFUFlSeTJRRHBCalhrL1BZNHpwbkYzQklRN3pQeXVKcmlqR0dwTmFDT3c3cXl2bGgwSXY0UVUzL0pmMFRWbUxteWlObEJLNVpMN25EV0JwZk1KUlJ5elVXZ2dxMUFYMXp1dndpV01KREZjMmVST0pOdkpxdXZ0TlR1M01sUm5RL29JOVBQWGNWdFhETFY3NEZMRVF3bWlmTUVhZVBxRzhvSjlQcnZmSlRMTnN1Q0xPYnMxVVI4dGU0eTJxS2xDQzFacVdYVitCWGM0WXROREhBbzNoN2xEbnVIOGRuUEozUjc0Z3dNcWE3L0dodjNUSWt1VlFmYzV0VDF4L25RR2pOdkZFVHZ2L1k3SWRsdkdsSU9BdE1UT09TRkRUWFNXZTVBN2I5T1pPU0Z4MTJZSjNxMHdnPT0iLCJhbGciOiJSUzI1NiJ9.eyJpc3MiOiJzb3JhY29tLmlvIiwiYXVkIjoiT3BlcmF0b3IiLCJleHAiOjE1Njc3NTgyNDEsImp0aSI6IjBXM0wwcGl6bjdpeVR4R0l4LV9OVGciLCJpYXQiOjE1Njc2NzE4NDEsIm5iZiI6MTU2NzY3MTcyMSwic3ViIjoic29yYWNvbSIsIm9wZXJhdG9yIjp7ImNvdmVyYWdlVHlwZXMiOlsianAiXSwicGVybWlzc2lvbnMiOlt7InN0YXRlbWVudHMiOlt7ImVmZmVjdCI6ImFsbG93IiwiYXBpIjpbIioiXX1dfV0sImFjY291bnRUeXBlIjoiMCIsInBheW1lbnRNZXRob2RTdGF0dXMiOiJ1bnJlZ2lzdGVyZWQiLCJvcGVyYXRvcklkIjoiT1AwMDgxMTg1MDQ5IiwiY292ZXJhZ2VUeXBlQXR0cmlidXRlcyI6eyJqcCI6eyJ0ZXJtc1ZlcnNpb24iOiIxIiwicGF5bWVudE1ldGhvZFN0YXR1cyI6InVucmVnaXN0ZXJlZCIsImNvbnRyYWN0cyI6W10sImNvbnRyYWN0RGV0YWlsIjp7fX19fX0.ZsNHqLw8TYlYW7nXh1Y_qd68S9V09yAPf0DyFy__CZSeDkcxV_Wk_D2DVLMMxgvrv4aJyQwjjad1mgL5kKKZgoGKrszKP9WErqI-y4IvCxwfbOJ_nmsp5SkwUbv8tlI9c-3o7ax-46TCNZYH9qxpKJWL53mA1QZmOJ3--0JbATDAVqKHjmi1-M74jWOgkh_kFk9N2ALvgskzTXLre1kZVkRn2p-C9CpYuoXx8eladkW01Ixp-qfVrWkeTkrYHjWDWiM0kI3vKY1DJosfknbTd2PN6gVRfLEARQpnceafjqLf-VfoUwJStxY94NKsxn3Yx4gWmXirnd2AuNLR2P5VqA' \
  -d '{
    "companyName": "株式会社CAMI&Co.",
    "department": "IoT Platform",
    "fullName": "神谷雅文"
  }' \
  'https://jp.api.soracom.io/v1/payment_statements/payer_information'

no content
```


## createShippingAddress

```
curl -X POST \
  --header 'Content-Type: application/json' \
  --header 'Accept: */*' \
  --header 'X-Soracom-API-Key: api-3904e648-dd53-447d-b2e9-927e320dcb8e' \
  --header 'X-Soracom-Token: eyJraWQiOiJBUUVDQUhnYmdGdnFrclRTbGlNVmNCQnV0VXlVcnNvU1RqTTM4NlR5WGVsaEdlUWtOd0FBQVk0d2dnR0tCZ2txaGtpRzl3MEJCd2FnZ2dGN01JSUJkd0lCQURDQ0FYQUdDU3FHU0liM0RRRUhBVEFlQmdsZ2hrZ0JaUU1FQVM0d0VRUU1uRWdLVlRiZGFsbWd4RGtkQWdFUWdJSUJRZlhXR1k1UHdqUjN4ZWY5SHhuZVo4NzN3THVHN3kzblY1TkZnTFZkNFdTaEdONTJBa1ZaVG55dG80RGY2UXVJWm9BS05KbFNqZWcyWnowRjV1S1p3amI0cy9pQlNCQno0bnZhcHdYQ0dOOFNjNHVMYVNKOUMzc2g3bmxFUFlSeTJRRHBCalhrL1BZNHpwbkYzQklRN3pQeXVKcmlqR0dwTmFDT3c3cXl2bGgwSXY0UVUzL0pmMFRWbUxteWlObEJLNVpMN25EV0JwZk1KUlJ5elVXZ2dxMUFYMXp1dndpV01KREZjMmVST0pOdkpxdXZ0TlR1M01sUm5RL29JOVBQWGNWdFhETFY3NEZMRVF3bWlmTUVhZVBxRzhvSjlQcnZmSlRMTnN1Q0xPYnMxVVI4dGU0eTJxS2xDQzFacVdYVitCWGM0WXROREhBbzNoN2xEbnVIOGRuUEozUjc0Z3dNcWE3L0dodjNUSWt1VlFmYzV0VDF4L25RR2pOdkZFVHZ2L1k3SWRsdkdsSU9BdE1UT09TRkRUWFNXZTVBN2I5T1pPU0Z4MTJZSjNxMHdnPT0iLCJhbGciOiJSUzI1NiJ9.eyJpc3MiOiJzb3JhY29tLmlvIiwiYXVkIjoiT3BlcmF0b3IiLCJleHAiOjE1Njc3NTgyNDEsImp0aSI6IjBXM0wwcGl6bjdpeVR4R0l4LV9OVGciLCJpYXQiOjE1Njc2NzE4NDEsIm5iZiI6MTU2NzY3MTcyMSwic3ViIjoic29yYWNvbSIsIm9wZXJhdG9yIjp7ImNvdmVyYWdlVHlwZXMiOlsianAiXSwicGVybWlzc2lvbnMiOlt7InN0YXRlbWVudHMiOlt7ImVmZmVjdCI6ImFsbG93IiwiYXBpIjpbIioiXX1dfV0sImFjY291bnRUeXBlIjoiMCIsInBheW1lbnRNZXRob2RTdGF0dXMiOiJ1bnJlZ2lzdGVyZWQiLCJvcGVyYXRvcklkIjoiT1AwMDgxMTg1MDQ5IiwiY292ZXJhZ2VUeXBlQXR0cmlidXRlcyI6eyJqcCI6eyJ0ZXJtc1ZlcnNpb24iOiIxIiwicGF5bWVudE1ldGhvZFN0YXR1cyI6InVucmVnaXN0ZXJlZCIsImNvbnRyYWN0cyI6W10sImNvbnRyYWN0RGV0YWlsIjp7fX19fX0.ZsNHqLw8TYlYW7nXh1Y_qd68S9V09yAPf0DyFy__CZSeDkcxV_Wk_D2DVLMMxgvrv4aJyQwjjad1mgL5kKKZgoGKrszKP9WErqI-y4IvCxwfbOJ_nmsp5SkwUbv8tlI9c-3o7ax-46TCNZYH9qxpKJWL53mA1QZmOJ3--0JbATDAVqKHjmi1-M74jWOgkh_kFk9N2ALvgskzTXLre1kZVkRn2p-C9CpYuoXx8eladkW01Ixp-qfVrWkeTkrYHjWDWiM0kI3vKY1DJosfknbTd2PN6gVRfLEARQpnceafjqLf-VfoUwJStxY94NKsxn3Yx4gWmXirnd2AuNLR2P5VqA' \
  -d '{
    "addressLine1": "東五反田 1-10-8",
    "addressLine2": "",
    "building": "五反田S&Lビル 8階",
    "city": "品川区",
    "companyName": "株式会社CAMI&Co.",
    "department": "IoT Platform",
    "fullName": "神谷雅文",
    "phoneNumber": "03-6417-9399",
    "state": "東京都",
    "zipCode": "141-0022"
  }' \
  'https://jp.api.soracom.io/v1/operators/OP0081185049/shipping_addresses'

{
  "countryCode": "JP",
  "zipCode": "141-0022",
  "state": "東京都",
  "city": "品川区",
  "addressLine1": "東五反田 1-10-8",
  "addressLine2": "",
  "building": "五反田S&Lビル 8階",
  "companyName": "株式会社CAMI&Co.",
  "department": "IoT Platform",
  "fullName": "神谷雅文",
  "phoneNumber": "03-6417-9399",
  "shippingAddressId": "c300add2-9844-4ab4-a1a6-30145340d856",
  "shippingArea": "kanto"
}
```


## confirmOrder

```
{
  "orderList": [
    {
      "orderId": "20190919091648_92e9a82e",
      "orderItemList": [
        {
          "product": {
            "productCode": "4573326590273",
            "productName": "SORACOM Air SIM card  plan-KM1  size:Nano(for data) 1 SIM pack1",
            "description": "This type of SIM provides cellular LPWA (LTE Cat. M1) connectivity. NOTE: Please be aware that communications charges for this type of service are significantly higher than for normal service. Cannot be used with regular LTE devices.",
            "count": 1,
            "price": 1500,
            "currency": "JPY",
            "properties": {
              "contractType": "no_sms",
              "simSubscription": "plan-KM1",
              "simSize": "nano"
            },
            "productType": "sim",
            "productInfoURL": "https://soracom.jp/products/sim/plan-km1/",
            "productImageURLs": []
          },
          "quantity": 2,
          "productAmount": 3000
        }
      ],
      "shippingAddressId": "c300add2-9844-4ab4-a1a6-30145340d856",
      "shippingAddress": {
        "countryCode": "JP",
        "zipCode": "141-0022",
        "state": "東京都",
        "city": "品川区",
        "addressLine1": "東五反田 1-10-8",
        "building": "五反田S&Lビル 8階",
        "companyName": "株式会社CAMI&Co.",
        "department": "IoT Platform",
        "fullName": "神谷雅文",
        "phoneNumber": "03-6417-9399"
      },
      "shippingCost": 907,
      "taxAmount": 240,
      "totalAmount": 4147,
      "email": "iot_dx_soracom@cami.jp",
      "currency": "JPY",
      "orderDateTime": "20190919091731",
      "orderStatus": "orderProcessing"
    }
  ]
}

```


## enableMFA: /operators/{operator_id}/mfa

```
curl -X POST \
  --header 'Content-Type: application/json' \
  --header 'Accept: application/json' \
  --header 'X-Soracom-API-Key: api-3904e648-dd53-447d-b2e9-927e320dcb8e' \
  --header 'X-Soracom-Token: eyJraWQiOiJBUUVDQUhnYmdGdnFrclRTbGlNVmNCQnV0VXlVcnNvU1RqTTM4NlR5WGVsaEdlUWtOd0FBQVk0d2dnR0tCZ2txaGtpRzl3MEJCd2FnZ2dGN01JSUJkd0lCQURDQ0FYQUdDU3FHU0liM0RRRUhBVEFlQmdsZ2hrZ0JaUU1FQVM0d0VRUU0zMlNvRisyZUI4S3ZKME03QWdFUWdJSUJRZjAxQlVRenBYM21qUzdPcHU5dThnVXB6MVFKRzl2SklMSGxXaEZuRy9ITDZ5VXkyeHBoOWVBK1pnMEN3ZXVrVWtmZXJPSmVJVHlwbmlvWDlXaHgweW9MdlZXMm9CcnpVemZVU2dlOGlkaVJicUNTaVdMU1BUclNnaWZYamZTaEdxRXlVQ2V2bVhndGRWWjFsSTU1RzQ1WGsxN3dtTDNUalB1VHR6WXh2S0R1Q2M3OXlUbDEvZ3J6Y2pmc0t0Y21ZYm5JbTc4M1RPRUJObElFWTRDZ0NrYmJkRkdadGtFRHpJRFhGeXFKSGJQY3h6SHJIZzd0emg0Qk52UkNrdzJlRlVLYkczYm10VmhBdHhpblNUQm9HVllYYThKa0JVRXFCTk9XdE5oWk50NVN6VTdnMHBBbTd0QklhT2dxQlhFR2JrUWk5czFFRU1GVUIxRWRRU1kyOTkrUUt0ZUJMZUVYaGd0bzJ1OUNRajYxSWpWVGtMQTk2VGVIN0NOcWVBd3V5Z2Q4Z0dMdDdrbUFZTk1NWTMrQ3FtZlorVENZcm9xTDZjM0FRMzhJaS8xanNnPT0iLCJhbGciOiJSUzI1NiJ9.eyJpc3MiOiJzb3JhY29tLmlvIiwiYXVkIjoiT3BlcmF0b3IiLCJleHAiOjE1Njc5MjE3OTAsImp0aSI6IkN5MjdvdW9vZDNhQ0JtcHpPbElBOEEiLCJpYXQiOjE1Njc4MzUzOTAsIm5iZiI6MTU2NzgzNTI3MCwic3ViIjoic29yYWNvbSIsIm9wZXJhdG9yIjp7ImNvdmVyYWdlVHlwZXMiOlsianAiXSwicGVybWlzc2lvbnMiOlt7InN0YXRlbWVudHMiOlt7ImVmZmVjdCI6ImFsbG93IiwiYXBpIjpbIioiXX1dfV0sImFjY291bnRUeXBlIjoiMCIsInBheW1lbnRNZXRob2RTdGF0dXMiOiJyZWdpc3RlcmVkIiwib3BlcmF0b3JJZCI6Ik9QMDA4MTE4NTA0OSIsImNvdmVyYWdlVHlwZUF0dHJpYnV0ZXMiOnsianAiOnsidGVybXNWZXJzaW9uIjoiMSIsInBheW1lbnRNZXRob2RTdGF0dXMiOiJyZWdpc3RlcmVkIiwiY29udHJhY3RzIjpbXSwiY29udHJhY3REZXRhaWwiOnt9fX19fQ.F2uSudhMg-iAHOiXyS2uQVtR2bo0rqwSYUctKlYmXD7H31-w7aEEZoC_gnH-VJhGn52Lb57LJvCwoHHWeQeg34MPM5w0JhJd4R2ka2N6k21L-MbSqWsE7VvaN2PhiogCYKd7bX0MMMCCcNuNqLPpJrBJoJ_6pE80OHEoR0fsDbGa4oxElu7IGFfjKAQXQOGZ8pLOiO6D22eBiVCj4NZpw_I3ib-dhLTqzFstpINfEh7nXGn1wVndGeL3WjHzlzDSRodOoILO-Jjrc2Ufoci0gHvKRajfnYUVv1gQbVjI_CyA2DMxveMuiaUSpdTHc1ra8dX5IolKu2VFTHhFwL0Kbg' \
  'https://jp.api.soracom.io/v1/operators/OP0081185049/mfa'

{
  "totpUri": "otpauth://totp/SORACOM:OP0081185049?secret=YTBHHXA73TY6NLPV&issuer=SORACOM"
}
```


スマホで認証

1. "enableMFA" を実行して、レスポンスとして "totpUri" を返す

2. MFA に用いるデバイスにて Google Authenticator などで mfaOTPcode を生成する

3. "verifyMFA" にて mfaOTPcode を body に入れて POST する

4. レスポンスで返ってくる backupCodes は必ず厳重に保管する


## /operators/{operator_id}/mfa/verify

```
curl -X POST \
  --header 'Content-Type: application/json' \
  --header 'Accept: application/json' \
  --header 'X-Soracom-API-Key: api-3904e648-dd53-447d-b2e9-927e320dcb8e' \
  --header 'X-Soracom-Token: eyJraWQiOiJBUUVDQUhnYmdGdnFrclRTbGlNVmNCQnV0VXlVcnNvU1RqTTM4NlR5WGVsaEdlUWtOd0FBQVk0d2dnR0tCZ2txaGtpRzl3MEJCd2FnZ2dGN01JSUJkd0lCQURDQ0FYQUdDU3FHU0liM0RRRUhBVEFlQmdsZ2hrZ0JaUU1FQVM0d0VRUU0zMlNvRisyZUI4S3ZKME03QWdFUWdJSUJRZjAxQlVRenBYM21qUzdPcHU5dThnVXB6MVFKRzl2SklMSGxXaEZuRy9ITDZ5VXkyeHBoOWVBK1pnMEN3ZXVrVWtmZXJPSmVJVHlwbmlvWDlXaHgweW9MdlZXMm9CcnpVemZVU2dlOGlkaVJicUNTaVdMU1BUclNnaWZYamZTaEdxRXlVQ2V2bVhndGRWWjFsSTU1RzQ1WGsxN3dtTDNUalB1VHR6WXh2S0R1Q2M3OXlUbDEvZ3J6Y2pmc0t0Y21ZYm5JbTc4M1RPRUJObElFWTRDZ0NrYmJkRkdadGtFRHpJRFhGeXFKSGJQY3h6SHJIZzd0emg0Qk52UkNrdzJlRlVLYkczYm10VmhBdHhpblNUQm9HVllYYThKa0JVRXFCTk9XdE5oWk50NVN6VTdnMHBBbTd0QklhT2dxQlhFR2JrUWk5czFFRU1GVUIxRWRRU1kyOTkrUUt0ZUJMZUVYaGd0bzJ1OUNRajYxSWpWVGtMQTk2VGVIN0NOcWVBd3V5Z2Q4Z0dMdDdrbUFZTk1NWTMrQ3FtZlorVENZcm9xTDZjM0FRMzhJaS8xanNnPT0iLCJhbGciOiJSUzI1NiJ9.eyJpc3MiOiJzb3JhY29tLmlvIiwiYXVkIjoiT3BlcmF0b3IiLCJleHAiOjE1Njc5MjE3OTAsImp0aSI6IkN5MjdvdW9vZDNhQ0JtcHpPbElBOEEiLCJpYXQiOjE1Njc4MzUzOTAsIm5iZiI6MTU2NzgzNTI3MCwic3ViIjoic29yYWNvbSIsIm9wZXJhdG9yIjp7ImNvdmVyYWdlVHlwZXMiOlsianAiXSwicGVybWlzc2lvbnMiOlt7InN0YXRlbWVudHMiOlt7ImVmZmVjdCI6ImFsbG93IiwiYXBpIjpbIioiXX1dfV0sImFjY291bnRUeXBlIjoiMCIsInBheW1lbnRNZXRob2RTdGF0dXMiOiJyZWdpc3RlcmVkIiwib3BlcmF0b3JJZCI6Ik9QMDA4MTE4NTA0OSIsImNvdmVyYWdlVHlwZUF0dHJpYnV0ZXMiOnsianAiOnsidGVybXNWZXJzaW9uIjoiMSIsInBheW1lbnRNZXRob2RTdGF0dXMiOiJyZWdpc3RlcmVkIiwiY29udHJhY3RzIjpbXSwiY29udHJhY3REZXRhaWwiOnt9fX19fQ.F2uSudhMg-iAHOiXyS2uQVtR2bo0rqwSYUctKlYmXD7H31-w7aEEZoC_gnH-VJhGn52Lb57LJvCwoHHWeQeg34MPM5w0JhJd4R2ka2N6k21L-MbSqWsE7VvaN2PhiogCYKd7bX0MMMCCcNuNqLPpJrBJoJ_6pE80OHEoR0fsDbGa4oxElu7IGFfjKAQXQOGZ8pLOiO6D22eBiVCj4NZpw_I3ib-dhLTqzFstpINfEh7nXGn1wVndGeL3WjHzlzDSRodOoILO-Jjrc2Ufoci0gHvKRajfnYUVv1gQbVjI_CyA2DMxveMuiaUSpdTHc1ra8dX5IolKu2VFTHhFwL0Kbg' \
  -d '{
    "mfaOTPCode": "799744"
  }' \
  'https://jp.api.soracom.io/v1/operators/OP0081185049/mfa/verify'

{
  "backupCodes": [
    "48690796",
    "41947456",
    "14598847",
    "42787185",
    "76037234"
  ]
}
```


// TODO: User(SAM)
// ToDO: Order





## createGroup: /groups

```
curl -X POST \
  --header 'Content-Type: application/json' \
  --header 'Accept: application/json' \
  --header 'X-Soracom-API-Key: api-3904e648-dd53-447d-b2e9-927e320dcb8e' \
  --header 'X-Soracom-Token: eyJraWQiOiJBUUVDQUhnYmdGdnFrclRTbGlNVmNCQnV0VXlVcnNvU1RqTTM4NlR5WGVsaEdlUWtOd0FBQVk0d2dnR0tCZ2txaGtpRzl3MEJCd2FnZ2dGN01JSUJkd0lCQURDQ0FYQUdDU3FHU0liM0RRRUhBVEFlQmdsZ2hrZ0JaUU1FQVM0d0VRUU0zMlNvRisyZUI4S3ZKME03QWdFUWdJSUJRZjAxQlVRenBYM21qUzdPcHU5dThnVXB6MVFKRzl2SklMSGxXaEZuRy9ITDZ5VXkyeHBoOWVBK1pnMEN3ZXVrVWtmZXJPSmVJVHlwbmlvWDlXaHgweW9MdlZXMm9CcnpVemZVU2dlOGlkaVJicUNTaVdMU1BUclNnaWZYamZTaEdxRXlVQ2V2bVhndGRWWjFsSTU1RzQ1WGsxN3dtTDNUalB1VHR6WXh2S0R1Q2M3OXlUbDEvZ3J6Y2pmc0t0Y21ZYm5JbTc4M1RPRUJObElFWTRDZ0NrYmJkRkdadGtFRHpJRFhGeXFKSGJQY3h6SHJIZzd0emg0Qk52UkNrdzJlRlVLYkczYm10VmhBdHhpblNUQm9HVllYYThKa0JVRXFCTk9XdE5oWk50NVN6VTdnMHBBbTd0QklhT2dxQlhFR2JrUWk5czFFRU1GVUIxRWRRU1kyOTkrUUt0ZUJMZUVYaGd0bzJ1OUNRajYxSWpWVGtMQTk2VGVIN0NOcWVBd3V5Z2Q4Z0dMdDdrbUFZTk1NWTMrQ3FtZlorVENZcm9xTDZjM0FRMzhJaS8xanNnPT0iLCJhbGciOiJSUzI1NiJ9.eyJpc3MiOiJzb3JhY29tLmlvIiwiYXVkIjoiT3BlcmF0b3IiLCJleHAiOjE1Njc3NTk3MDIsImp0aSI6IjI2MUgxU3VZNDV6LWlvcE1FRlhrVGciLCJpYXQiOjE1Njc2NzMzMDIsIm5iZiI6MTU2NzY3MzE4Miwic3ViIjoic29yYWNvbSIsIm9wZXJhdG9yIjp7ImNvdmVyYWdlVHlwZXMiOlsianAiXSwicGVybWlzc2lvbnMiOlt7InN0YXRlbWVudHMiOlt7ImVmZmVjdCI6ImFsbG93IiwiYXBpIjpbIioiXX1dfV0sImFjY291bnRUeXBlIjoiMCIsInBheW1lbnRNZXRob2RTdGF0dXMiOiJ1bnJlZ2lzdGVyZWQiLCJvcGVyYXRvcklkIjoiT1AwMDgxMTg1MDQ5IiwiY292ZXJhZ2VUeXBlQXR0cmlidXRlcyI6eyJqcCI6eyJ0ZXJtc1ZlcnNpb24iOiIxIiwicGF5bWVudE1ldGhvZFN0YXR1cyI6InVucmVnaXN0ZXJlZCIsImNvbnRyYWN0cyI6W10sImNvbnRyYWN0RGV0YWlsIjp7fX19fX0.BU0FeoXtpq0DOaOckouzIM366vjEfgYIAGuEPs6rESOAtxV6S_sk7IM4MfH5iLYfXL-Sv1skC-NH8XFh1D-jNXodETCgiAG5Tt6drwJCvpAfArWfjhIGd78Cskjt7CWhbLvdJ4jCKIOSHnkfQw3XITprvy4jpzPijWC-bniRy3ChbYOAyfM6uM_ZncZCr5to9UW6NTAN-Ek1rv6ymMCQWbHZWJyj48-dCID1m1cR8eDAuBXlTU9Zirlh9IKUkraWUwn409UDiZrJP-YshlG_V6QWlz3wTNT3ExxfMSMZkvryFPNSuVvSMB5Y7JitZXCPbYMsQTorzjMXXG8LJllHRA' \
  -d '{
    "tags": {
      "name": "CustomerManagement"
    }
  }' \
  'https://jp.api.soracom.io/v1/groups'

{
  "operatorId": "OP0081185049",
  "groupId": "7300d51b-8145-44f6-b644-335ccf41834d",
  "createdAt": 1567673660892,
  "lastModifiedAt": 1567673660892,
  "configuration": {},
  "tags": {
    "name": "CustomerManagement"
  },
  "createdTime": 1567673660892,
  "lastModifiedTime": 1567673660892
}
```


## /subscribers/{imsi}/activate

`状態` を `使用中` に変更。

```
curl -X POST \
  --header 'Content-Type: text/plain' \
  --header 'Accept: application/json' \
  --header 'X-Soracom-API-Key: api-3904e648-dd53-447d-b2e9-927e320dcb8e' \
  --header 'X-Soracom-Token: eyJraWQiOiJBUUVDQUhnYmdGdnFrclRTbGlNVmNCQnV0VXlVcnNvU1RqTTM4NlR5WGVsaEdlUWtOd0FBQVk0d2dnR0tCZ2txaGtpRzl3MEJCd2FnZ2dGN01JSUJkd0lCQURDQ0FYQUdDU3FHU0liM0RRRUhBVEFlQmdsZ2hrZ0JaUU1FQVM0d0VRUU0zMlNvRisyZUI4S3ZKME03QWdFUWdJSUJRZjAxQlVRenBYM21qUzdPcHU5dThnVXB6MVFKRzl2SklMSGxXaEZuRy9ITDZ5VXkyeHBoOWVBK1pnMEN3ZXVrVWtmZXJPSmVJVHlwbmlvWDlXaHgweW9MdlZXMm9CcnpVemZVU2dlOGlkaVJicUNTaVdMU1BUclNnaWZYamZTaEdxRXlVQ2V2bVhndGRWWjFsSTU1RzQ1WGsxN3dtTDNUalB1VHR6WXh2S0R1Q2M3OXlUbDEvZ3J6Y2pmc0t0Y21ZYm5JbTc4M1RPRUJObElFWTRDZ0NrYmJkRkdadGtFRHpJRFhGeXFKSGJQY3h6SHJIZzd0emg0Qk52UkNrdzJlRlVLYkczYm10VmhBdHhpblNUQm9HVllYYThKa0JVRXFCTk9XdE5oWk50NVN6VTdnMHBBbTd0QklhT2dxQlhFR2JrUWk5czFFRU1GVUIxRWRRU1kyOTkrUUt0ZUJMZUVYaGd0bzJ1OUNRajYxSWpWVGtMQTk2VGVIN0NOcWVBd3V5Z2Q4Z0dMdDdrbUFZTk1NWTMrQ3FtZlorVENZcm9xTDZjM0FRMzhJaS8xanNnPT0iLCJhbGciOiJSUzI1NiJ9.eyJpc3MiOiJzb3JhY29tLmlvIiwiYXVkIjoiT3BlcmF0b3IiLCJleHAiOjE1Njc3NTk3MDIsImp0aSI6IjI2MUgxU3VZNDV6LWlvcE1FRlhrVGciLCJpYXQiOjE1Njc2NzMzMDIsIm5iZiI6MTU2NzY3MzE4Miwic3ViIjoic29yYWNvbSIsIm9wZXJhdG9yIjp7ImNvdmVyYWdlVHlwZXMiOlsianAiXSwicGVybWlzc2lvbnMiOlt7InN0YXRlbWVudHMiOlt7ImVmZmVjdCI6ImFsbG93IiwiYXBpIjpbIioiXX1dfV0sImFjY291bnRUeXBlIjoiMCIsInBheW1lbnRNZXRob2RTdGF0dXMiOiJ1bnJlZ2lzdGVyZWQiLCJvcGVyYXRvcklkIjoiT1AwMDgxMTg1MDQ5IiwiY292ZXJhZ2VUeXBlQXR0cmlidXRlcyI6eyJqcCI6eyJ0ZXJtc1ZlcnNpb24iOiIxIiwicGF5bWVudE1ldGhvZFN0YXR1cyI6InVucmVnaXN0ZXJlZCIsImNvbnRyYWN0cyI6W10sImNvbnRyYWN0RGV0YWlsIjp7fX19fX0.BU0FeoXtpq0DOaOckouzIM366vjEfgYIAGuEPs6rESOAtxV6S_sk7IM4MfH5iLYfXL-Sv1skC-NH8XFh1D-jNXodETCgiAG5Tt6drwJCvpAfArWfjhIGd78Cskjt7CWhbLvdJ4jCKIOSHnkfQw3XITprvy4jpzPijWC-bniRy3ChbYOAyfM6uM_ZncZCr5to9UW6NTAN-Ek1rv6ymMCQWbHZWJyj48-dCID1m1cR8eDAuBXlTU9Zirlh9IKUkraWUwn409UDiZrJP-YshlG_V6QWlz3wTNT3ExxfMSMZkvryFPNSuVvSMB5Y7JitZXCPbYMsQTorzjMXXG8LJllHRA' \
  'https://jp.api.soracom.io/v1/subscribers/440525060023501/activate'

{
  "imsi": "440525060023501",
  "msisdn": "812025372219",
  "ipAddress": null,
  "operatorId": "OP0081185049",
  "apn": "soracom.io",
  "type": "t1.standard",
  "groupId": null,
  "createdAt": 1563786879213,
  "lastModifiedAt": 1567674492668,
  "expiredAt": null,
  "registeredTime": null,
  "expiryAction": null,
  "terminationEnabled": false,
  "status": "active",
  "tags": {},
  "sessionStatus": null,
  "imeiLock": null,
  "speedClass": "t1.standard",
  "moduleType": "nano",
  "plan": 0,
  "iccid": "8981300025200020011",
  "serialNumber": "8981300025200020011",
  "subscription": "plan-KM1",
  "createdTime": 1563786879213,
  "expiryTime": null,
  "lastModifiedTime": 1567674492668
}
```


## /subscribers/{imsi}/set_group

```
curl -X POST \
  --header 'Content-Type: application/json' \
  --header 'Accept: application/json' \
  --header 'X-Soracom-API-Key: api-3904e648-dd53-447d-b2e9-927e320dcb8e' \
  --header 'X-Soracom-Token: eyJraWQiOiJBUUVDQUhnYmdGdnFrclRTbGlNVmNCQnV0VXlVcnNvU1RqTTM4NlR5WGVsaEdlUWtOd0FBQVk0d2dnR0tCZ2txaGtpRzl3MEJCd2FnZ2dGN01JSUJkd0lCQURDQ0FYQUdDU3FHU0liM0RRRUhBVEFlQmdsZ2hrZ0JaUU1FQVM0d0VRUU0zMlNvRisyZUI4S3ZKME03QWdFUWdJSUJRZjAxQlVRenBYM21qUzdPcHU5dThnVXB6MVFKRzl2SklMSGxXaEZuRy9ITDZ5VXkyeHBoOWVBK1pnMEN3ZXVrVWtmZXJPSmVJVHlwbmlvWDlXaHgweW9MdlZXMm9CcnpVemZVU2dlOGlkaVJicUNTaVdMU1BUclNnaWZYamZTaEdxRXlVQ2V2bVhndGRWWjFsSTU1RzQ1WGsxN3dtTDNUalB1VHR6WXh2S0R1Q2M3OXlUbDEvZ3J6Y2pmc0t0Y21ZYm5JbTc4M1RPRUJObElFWTRDZ0NrYmJkRkdadGtFRHpJRFhGeXFKSGJQY3h6SHJIZzd0emg0Qk52UkNrdzJlRlVLYkczYm10VmhBdHhpblNUQm9HVllYYThKa0JVRXFCTk9XdE5oWk50NVN6VTdnMHBBbTd0QklhT2dxQlhFR2JrUWk5czFFRU1GVUIxRWRRU1kyOTkrUUt0ZUJMZUVYaGd0bzJ1OUNRajYxSWpWVGtMQTk2VGVIN0NOcWVBd3V5Z2Q4Z0dMdDdrbUFZTk1NWTMrQ3FtZlorVENZcm9xTDZjM0FRMzhJaS8xanNnPT0iLCJhbGciOiJSUzI1NiJ9.eyJpc3MiOiJzb3JhY29tLmlvIiwiYXVkIjoiT3BlcmF0b3IiLCJleHAiOjE1Njc3NTk3MDIsImp0aSI6IjI2MUgxU3VZNDV6LWlvcE1FRlhrVGciLCJpYXQiOjE1Njc2NzMzMDIsIm5iZiI6MTU2NzY3MzE4Miwic3ViIjoic29yYWNvbSIsIm9wZXJhdG9yIjp7ImNvdmVyYWdlVHlwZXMiOlsianAiXSwicGVybWlzc2lvbnMiOlt7InN0YXRlbWVudHMiOlt7ImVmZmVjdCI6ImFsbG93IiwiYXBpIjpbIioiXX1dfV0sImFjY291bnRUeXBlIjoiMCIsInBheW1lbnRNZXRob2RTdGF0dXMiOiJ1bnJlZ2lzdGVyZWQiLCJvcGVyYXRvcklkIjoiT1AwMDgxMTg1MDQ5IiwiY292ZXJhZ2VUeXBlQXR0cmlidXRlcyI6eyJqcCI6eyJ0ZXJtc1ZlcnNpb24iOiIxIiwicGF5bWVudE1ldGhvZFN0YXR1cyI6InVucmVnaXN0ZXJlZCIsImNvbnRyYWN0cyI6W10sImNvbnRyYWN0RGV0YWlsIjp7fX19fX0.BU0FeoXtpq0DOaOckouzIM366vjEfgYIAGuEPs6rESOAtxV6S_sk7IM4MfH5iLYfXL-Sv1skC-NH8XFh1D-jNXodETCgiAG5Tt6drwJCvpAfArWfjhIGd78Cskjt7CWhbLvdJ4jCKIOSHnkfQw3XITprvy4jpzPijWC-bniRy3ChbYOAyfM6uM_ZncZCr5to9UW6NTAN-Ek1rv6ymMCQWbHZWJyj48-dCID1m1cR8eDAuBXlTU9Zirlh9IKUkraWUwn409UDiZrJP-YshlG_V6QWlz3wTNT3ExxfMSMZkvryFPNSuVvSMB5Y7JitZXCPbYMsQTorzjMXXG8LJllHRA' \
  -d '{"groupId": "7300d51b-8145-44f6-b644-335ccf41834d"}' \
  'https://jp.api.soracom.io/v1/subscribers/440525060023501/set_group'

{
  "imsi": "440525060023501",
  "msisdn": "812025372219",
  "ipAddress": null,
  "operatorId": "OP0081185049",
  "apn": "soracom.io",
  "type": "t1.standard",
  "groupId": "7300d51b-8145-44f6-b644-335ccf41834d",
  "createdAt": 1563786879213,
  "lastModifiedAt": 1567674712353,
  "expiredAt": null,
  "registeredTime": null,
  "expiryAction": null,
  "terminationEnabled": false,
  "status": "active",
  "tags": {},
  "sessionStatus": null,
  "imeiLock": null,
  "speedClass": "t1.standard",
  "moduleType": "nano",
  "plan": 0,
  "iccid": "8981300025200020011",
  "serialNumber": "8981300025200020011",
  "subscription": "plan-KM1",
  "createdTime": 1563786879213,
  "expiryTime": null,
  "lastModifiedTime": 1567674712353
}
```

## /groups/{group_id}/configuration/{namespace}

```
curl -X PUT \
  --header 'Content-Type: application/json' \
  --header 'Accept: application/json' \
  --header 'X-Soracom-API-Key: api-3904e648-dd53-447d-b2e9-927e320dcb8e' \
  --header 'X-Soracom-Token: eyJraWQiOiJBUUVDQUhnYmdGdnFrclRTbGlNVmNCQnV0VXlVcnNvU1RqTTM4NlR5WGVsaEdlUWtOd0FBQVk0d2dnR0tCZ2txaGtpRzl3MEJCd2FnZ2dGN01JSUJkd0lCQURDQ0FYQUdDU3FHU0liM0RRRUhBVEFlQmdsZ2hrZ0JaUU1FQVM0d0VRUU0zMlNvRisyZUI4S3ZKME03QWdFUWdJSUJRZjAxQlVRenBYM21qUzdPcHU5dThnVXB6MVFKRzl2SklMSGxXaEZuRy9ITDZ5VXkyeHBoOWVBK1pnMEN3ZXVrVWtmZXJPSmVJVHlwbmlvWDlXaHgweW9MdlZXMm9CcnpVemZVU2dlOGlkaVJicUNTaVdMU1BUclNnaWZYamZTaEdxRXlVQ2V2bVhndGRWWjFsSTU1RzQ1WGsxN3dtTDNUalB1VHR6WXh2S0R1Q2M3OXlUbDEvZ3J6Y2pmc0t0Y21ZYm5JbTc4M1RPRUJObElFWTRDZ0NrYmJkRkdadGtFRHpJRFhGeXFKSGJQY3h6SHJIZzd0emg0Qk52UkNrdzJlRlVLYkczYm10VmhBdHhpblNUQm9HVllYYThKa0JVRXFCTk9XdE5oWk50NVN6VTdnMHBBbTd0QklhT2dxQlhFR2JrUWk5czFFRU1GVUIxRWRRU1kyOTkrUUt0ZUJMZUVYaGd0bzJ1OUNRajYxSWpWVGtMQTk2VGVIN0NOcWVBd3V5Z2Q4Z0dMdDdrbUFZTk1NWTMrQ3FtZlorVENZcm9xTDZjM0FRMzhJaS8xanNnPT0iLCJhbGciOiJSUzI1NiJ9.eyJpc3MiOiJzb3JhY29tLmlvIiwiYXVkIjoiT3BlcmF0b3IiLCJleHAiOjE1Njc5MjE3OTAsImp0aSI6IkN5MjdvdW9vZDNhQ0JtcHpPbElBOEEiLCJpYXQiOjE1Njc4MzUzOTAsIm5iZiI6MTU2NzgzNTI3MCwic3ViIjoic29yYWNvbSIsIm9wZXJhdG9yIjp7ImNvdmVyYWdlVHlwZXMiOlsianAiXSwicGVybWlzc2lvbnMiOlt7InN0YXRlbWVudHMiOlt7ImVmZmVjdCI6ImFsbG93IiwiYXBpIjpbIioiXX1dfV0sImFjY291bnRUeXBlIjoiMCIsInBheW1lbnRNZXRob2RTdGF0dXMiOiJyZWdpc3RlcmVkIiwib3BlcmF0b3JJZCI6Ik9QMDA4MTE4NTA0OSIsImNvdmVyYWdlVHlwZUF0dHJpYnV0ZXMiOnsianAiOnsidGVybXNWZXJzaW9uIjoiMSIsInBheW1lbnRNZXRob2RTdGF0dXMiOiJyZWdpc3RlcmVkIiwiY29udHJhY3RzIjpbXSwiY29udHJhY3REZXRhaWwiOnt9fX19fQ.F2uSudhMg-iAHOiXyS2uQVtR2bo0rqwSYUctKlYmXD7H31-w7aEEZoC_gnH-VJhGn52Lb57LJvCwoHHWeQeg34MPM5w0JhJd4R2ka2N6k21L-MbSqWsE7VvaN2PhiogCYKd7bX0MMMCCcNuNqLPpJrBJoJ_6pE80OHEoR0fsDbGa4oxElu7IGFfjKAQXQOGZ8pLOiO6D22eBiVCj4NZpw_I3ib-dhLTqzFstpINfEh7nXGn1wVndGeL3WjHzlzDSRodOoILO-Jjrc2Ufoci0gHvKRajfnYUVv1gQbVjI_CyA2DMxveMuiaUSpdTHc1ra8dX5IolKu2VFTHhFwL0Kbg' \
  -d '[
    {
      "key": "response",
      "value": {
          "format": "SoracomHarvest"
        }
    },
    {
      "key": "enabled",
      "value": true
    }
  ]' \
  'https://jp.api.soracom.io/v1/groups/7300d51b-8145-44f6-b644-335ccf41834d/configuration/UnifiedEndpoint'
 
curl -X PUT \
  --header 'Content-Type: application/json' \
  --header 'Accept: application/json' \
  --header 'X-Soracom-API-Key: api-3904e648-dd53-447d-b2e9-927e320dcb8e' \
  --header 'X-Soracom-Token: eyJraWQiOiJBUUVDQUhnYmdGdnFrclRTbGlNVmNCQnV0VXlVcnNvU1RqTTM4NlR5WGVsaEdlUWtOd0FBQVk0d2dnR0tCZ2txaGtpRzl3MEJCd2FnZ2dGN01JSUJkd0lCQURDQ0FYQUdDU3FHU0liM0RRRUhBVEFlQmdsZ2hrZ0JaUU1FQVM0d0VRUU0zMlNvRisyZUI4S3ZKME03QWdFUWdJSUJRZjAxQlVRenBYM21qUzdPcHU5dThnVXB6MVFKRzl2SklMSGxXaEZuRy9ITDZ5VXkyeHBoOWVBK1pnMEN3ZXVrVWtmZXJPSmVJVHlwbmlvWDlXaHgweW9MdlZXMm9CcnpVemZVU2dlOGlkaVJicUNTaVdMU1BUclNnaWZYamZTaEdxRXlVQ2V2bVhndGRWWjFsSTU1RzQ1WGsxN3dtTDNUalB1VHR6WXh2S0R1Q2M3OXlUbDEvZ3J6Y2pmc0t0Y21ZYm5JbTc4M1RPRUJObElFWTRDZ0NrYmJkRkdadGtFRHpJRFhGeXFKSGJQY3h6SHJIZzd0emg0Qk52UkNrdzJlRlVLYkczYm10VmhBdHhpblNUQm9HVllYYThKa0JVRXFCTk9XdE5oWk50NVN6VTdnMHBBbTd0QklhT2dxQlhFR2JrUWk5czFFRU1GVUIxRWRRU1kyOTkrUUt0ZUJMZUVYaGd0bzJ1OUNRajYxSWpWVGtMQTk2VGVIN0NOcWVBd3V5Z2Q4Z0dMdDdrbUFZTk1NWTMrQ3FtZlorVENZcm9xTDZjM0FRMzhJaS8xanNnPT0iLCJhbGciOiJSUzI1NiJ9.eyJpc3MiOiJzb3JhY29tLmlvIiwiYXVkIjoiT3BlcmF0b3IiLCJleHAiOjE1Njc3NjQ2NTgsImp0aSI6ImRVM0FVdVJRX2xhM1V4WmF1bVRKWlEiLCJpYXQiOjE1Njc2NzgyNTgsIm5iZiI6MTU2NzY3ODEzOCwic3ViIjoic29yYWNvbSIsIm9wZXJhdG9yIjp7ImNvdmVyYWdlVHlwZXMiOlsianAiXSwicGVybWlzc2lvbnMiOlt7InN0YXRlbWVudHMiOlt7ImVmZmVjdCI6ImFsbG93IiwiYXBpIjpbIioiXX1dfV0sImFjY291bnRUeXBlIjoiMCIsInBheW1lbnRNZXRob2RTdGF0dXMiOiJyZWdpc3RlcmVkIiwib3BlcmF0b3JJZCI6Ik9QMDA4MTE4NTA0OSIsImNvdmVyYWdlVHlwZUF0dHJpYnV0ZXMiOnsianAiOnsidGVybXNWZXJzaW9uIjoiMSIsInBheW1lbnRNZXRob2RTdGF0dXMiOiJyZWdpc3RlcmVkIiwiY29udHJhY3RzIjpbXSwiY29udHJhY3REZXRhaWwiOnt9fX19fQ.ZGAPsSXHtVE5qd15VMtfBMFeIZjo1kfZuFM6hnUDj5WkBIJO8EBvRSdNZkBsLzc47HBsmsqB7x4jBzeDl8wh4xwGBJRNtI-_tlhjnbD5BlV6dXIIfpIzQsdGdCqjiksUjZOCXpo1FzzVqvprFpcorP9dovHg66oQ3fBU6-5J_Zm_iT8bozV9QOEgDWOSRll0bJtXkR2jHmWHoQjvyUaLez2w31u_JbkxlxZQ8HoQYrxpNPRtZI9mOJqLKsQyag2BeT6sV0tbu_kF_mrV82mGZYv0LLD_PEthA8IE_lFJk5bF8jYV47XybIRwwScjCpVtm1Xu8c4d0U7CAc2ehcbhyg' \
  -d '[
    {
      "key": "binaryParserEnabled",
      "value": false
    }
  ]' \
  'https://jp.api.soracom.io/v1/groups/7300d51b-8145-44f6-b644-335ccf41834d/configuration/SoracomAir'
    
curl -X PUT \
  --header 'Content-Type: application/json' \
  --header 'Accept: application/json' \
  --header 'X-Soracom-API-Key: api-3904e648-dd53-447d-b2e9-927e320dcb8e' \
  --header 'X-Soracom-Token: eyJraWQiOiJBUUVDQUhnYmdGdnFrclRTbGlNVmNCQnV0VXlVcnNvU1RqTTM4NlR5WGVsaEdlUWtOd0FBQVk0d2dnR0tCZ2txaGtpRzl3MEJCd2FnZ2dGN01JSUJkd0lCQURDQ0FYQUdDU3FHU0liM0RRRUhBVEFlQmdsZ2hrZ0JaUU1FQVM0d0VRUU0zMlNvRisyZUI4S3ZKME03QWdFUWdJSUJRZjAxQlVRenBYM21qUzdPcHU5dThnVXB6MVFKRzl2SklMSGxXaEZuRy9ITDZ5VXkyeHBoOWVBK1pnMEN3ZXVrVWtmZXJPSmVJVHlwbmlvWDlXaHgweW9MdlZXMm9CcnpVemZVU2dlOGlkaVJicUNTaVdMU1BUclNnaWZYamZTaEdxRXlVQ2V2bVhndGRWWjFsSTU1RzQ1WGsxN3dtTDNUalB1VHR6WXh2S0R1Q2M3OXlUbDEvZ3J6Y2pmc0t0Y21ZYm5JbTc4M1RPRUJObElFWTRDZ0NrYmJkRkdadGtFRHpJRFhGeXFKSGJQY3h6SHJIZzd0emg0Qk52UkNrdzJlRlVLYkczYm10VmhBdHhpblNUQm9HVllYYThKa0JVRXFCTk9XdE5oWk50NVN6VTdnMHBBbTd0QklhT2dxQlhFR2JrUWk5czFFRU1GVUIxRWRRU1kyOTkrUUt0ZUJMZUVYaGd0bzJ1OUNRajYxSWpWVGtMQTk2VGVIN0NOcWVBd3V5Z2Q4Z0dMdDdrbUFZTk1NWTMrQ3FtZlorVENZcm9xTDZjM0FRMzhJaS8xanNnPT0iLCJhbGciOiJSUzI1NiJ9.eyJpc3MiOiJzb3JhY29tLmlvIiwiYXVkIjoiT3BlcmF0b3IiLCJleHAiOjE1Njc3NjQ2NTgsImp0aSI6ImRVM0FVdVJRX2xhM1V4WmF1bVRKWlEiLCJpYXQiOjE1Njc2NzgyNTgsIm5iZiI6MTU2NzY3ODEzOCwic3ViIjoic29yYWNvbSIsIm9wZXJhdG9yIjp7ImNvdmVyYWdlVHlwZXMiOlsianAiXSwicGVybWlzc2lvbnMiOlt7InN0YXRlbWVudHMiOlt7ImVmZmVjdCI6ImFsbG93IiwiYXBpIjpbIioiXX1dfV0sImFjY291bnRUeXBlIjoiMCIsInBheW1lbnRNZXRob2RTdGF0dXMiOiJyZWdpc3RlcmVkIiwib3BlcmF0b3JJZCI6Ik9QMDA4MTE4NTA0OSIsImNvdmVyYWdlVHlwZUF0dHJpYnV0ZXMiOnsianAiOnsidGVybXNWZXJzaW9uIjoiMSIsInBheW1lbnRNZXRob2RTdGF0dXMiOiJyZWdpc3RlcmVkIiwiY29udHJhY3RzIjpbXSwiY29udHJhY3REZXRhaWwiOnt9fX19fQ.ZGAPsSXHtVE5qd15VMtfBMFeIZjo1kfZuFM6hnUDj5WkBIJO8EBvRSdNZkBsLzc47HBsmsqB7x4jBzeDl8wh4xwGBJRNtI-_tlhjnbD5BlV6dXIIfpIzQsdGdCqjiksUjZOCXpo1FzzVqvprFpcorP9dovHg66oQ3fBU6-5J_Zm_iT8bozV9QOEgDWOSRll0bJtXkR2jHmWHoQjvyUaLez2w31u_JbkxlxZQ8HoQYrxpNPRtZI9mOJqLKsQyag2BeT6sV0tbu_kF_mrV82mGZYv0LLD_PEthA8IE_lFJk5bF8jYV47XybIRwwScjCpVtm1Xu8c4d0U7CAc2ehcbhyg' \
  -d '[
    {
      "key": "enabled",
      "value": true
    }
  ]' \
  'https://jp.api.soracom.io/v1/groups/7300d51b-8145-44f6-b644-335ccf41834d/configuration/SoracomHarvest'
      
{
  "operatorId": "OP0081185049",
  "groupId": "7300d51b-8145-44f6-b644-335ccf41834d",
  "createdAt": 1567673660892,
  "lastModifiedAt": 1567835870188,
  "configuration": {
    "SoracomHarvest": {
      "enabled": true
    },
    "UnifiedEndpoint": {
      "response": {
        "format": "SoracomHarvest"
      },
      "enabled": true
    },
    "SoracomAir": {
      "binaryParserEnabled": false
    }
  },
  "tags": {
    "name": "CustomerManagement"
  },
  "createdTime": 1567673660892,
  "lastModifiedTime": 1567835870188
}
```


## /subscribers/{imsi}/set_imei_lock

```
curl -X POST \
  --header 'Content-Type: application/json' \
  --header 'Accept: application/json' \
  --header 'X-Soracom-API-Key: api-3904e648-dd53-447d-b2e9-927e320dcb8e' \
  --header 'X-Soracom-Token: eyJraWQiOiJBUUVDQUhnYmdGdnFrclRTbGlNVmNCQnV0VXlVcnNvU1RqTTM4NlR5WGVsaEdlUWtOd0FBQVk0d2dnR0tCZ2txaGtpRzl3MEJCd2FnZ2dGN01JSUJkd0lCQURDQ0FYQUdDU3FHU0liM0RRRUhBVEFlQmdsZ2hrZ0JaUU1FQVM0d0VRUU0zMlNvRisyZUI4S3ZKME03QWdFUWdJSUJRZjAxQlVRenBYM21qUzdPcHU5dThnVXB6MVFKRzl2SklMSGxXaEZuRy9ITDZ5VXkyeHBoOWVBK1pnMEN3ZXVrVWtmZXJPSmVJVHlwbmlvWDlXaHgweW9MdlZXMm9CcnpVemZVU2dlOGlkaVJicUNTaVdMU1BUclNnaWZYamZTaEdxRXlVQ2V2bVhndGRWWjFsSTU1RzQ1WGsxN3dtTDNUalB1VHR6WXh2S0R1Q2M3OXlUbDEvZ3J6Y2pmc0t0Y21ZYm5JbTc4M1RPRUJObElFWTRDZ0NrYmJkRkdadGtFRHpJRFhGeXFKSGJQY3h6SHJIZzd0emg0Qk52UkNrdzJlRlVLYkczYm10VmhBdHhpblNUQm9HVllYYThKa0JVRXFCTk9XdE5oWk50NVN6VTdnMHBBbTd0QklhT2dxQlhFR2JrUWk5czFFRU1GVUIxRWRRU1kyOTkrUUt0ZUJMZUVYaGd0bzJ1OUNRajYxSWpWVGtMQTk2VGVIN0NOcWVBd3V5Z2Q4Z0dMdDdrbUFZTk1NWTMrQ3FtZlorVENZcm9xTDZjM0FRMzhJaS8xanNnPT0iLCJhbGciOiJSUzI1NiJ9.eyJpc3MiOiJzb3JhY29tLmlvIiwiYXVkIjoiT3BlcmF0b3IiLCJleHAiOjE1Njc3NjQ2NTgsImp0aSI6ImRVM0FVdVJRX2xhM1V4WmF1bVRKWlEiLCJpYXQiOjE1Njc2NzgyNTgsIm5iZiI6MTU2NzY3ODEzOCwic3ViIjoic29yYWNvbSIsIm9wZXJhdG9yIjp7ImNvdmVyYWdlVHlwZXMiOlsianAiXSwicGVybWlzc2lvbnMiOlt7InN0YXRlbWVudHMiOlt7ImVmZmVjdCI6ImFsbG93IiwiYXBpIjpbIioiXX1dfV0sImFjY291bnRUeXBlIjoiMCIsInBheW1lbnRNZXRob2RTdGF0dXMiOiJyZWdpc3RlcmVkIiwib3BlcmF0b3JJZCI6Ik9QMDA4MTE4NTA0OSIsImNvdmVyYWdlVHlwZUF0dHJpYnV0ZXMiOnsianAiOnsidGVybXNWZXJzaW9uIjoiMSIsInBheW1lbnRNZXRob2RTdGF0dXMiOiJyZWdpc3RlcmVkIiwiY29udHJhY3RzIjpbXSwiY29udHJhY3REZXRhaWwiOnt9fX19fQ.ZGAPsSXHtVE5qd15VMtfBMFeIZjo1kfZuFM6hnUDj5WkBIJO8EBvRSdNZkBsLzc47HBsmsqB7x4jBzeDl8wh4xwGBJRNtI-_tlhjnbD5BlV6dXIIfpIzQsdGdCqjiksUjZOCXpo1FzzVqvprFpcorP9dovHg66oQ3fBU6-5J_Zm_iT8bozV9QOEgDWOSRll0bJtXkR2jHmWHoQjvyUaLez2w31u_JbkxlxZQ8HoQYrxpNPRtZI9mOJqLKsQyag2BeT6sV0tbu_kF_mrV82mGZYv0LLD_PEthA8IE_lFJk5bF8jYV47XybIRwwScjCpVtm1Xu8c4d0U7CAc2ehcbhyg' \
  -d '{
    "imei": "866425033400716"
  }' \
  'https://jp.api.soracom.io/v1/subscribers/440525060023501/set_imei_lock'

{
  "imsi": "440525060023501",
  "msisdn": "812025372219",
  "ipAddress": "10.134.233.97",
  "operatorId": "OP0081185049",
  "apn": "soracom.io",
  "type": "t1.standard",
  "groupId": "7300d51b-8145-44f6-b644-335ccf41834d",
  "createdAt": 1563786879213,
  "lastModifiedAt": 1567684525067,
  "expiredAt": null,
  "registeredTime": null,
  "expiryAction": null,
  "terminationEnabled": false,
  "status": "active",
  "tags": {},
  "sessionStatus": {
    "lastUpdatedAt": 1567684521983,
    "imei": null,
    "location": null,
    "ueIpAddress": null,
    "dnsServers": null,
    "online": false
  },
  "imeiLock": {
    "imei": "866425033400716"
  },
  "speedClass": "t1.standard",
  "moduleType": "nano",
  "plan": 0,
  "iccid": "8981300025200020011",
  "serialNumber": "8981300025200020011",
  "subscription": "plan-KM1",
  "createdTime": 1563786879213,
  "expiryTime": null,
  "lastModifiedTime": 1567684525067
}
```


## /subscribers/{imsi}/tags

```
curl -X PUT \
  --header 'Content-Type: application/json' \
  --header 'Accept: application/json' \
  --header 'X-Soracom-API-Key: api-3904e648-dd53-447d-b2e9-927e320dcb8e' \
  --header 'X-Soracom-Token: eyJraWQiOiJBUUVDQUhnYmdGdnFrclRTbGlNVmNCQnV0VXlVcnNvU1RqTTM4NlR5WGVsaEdlUWtOd0FBQVk0d2dnR0tCZ2txaGtpRzl3MEJCd2FnZ2dGN01JSUJkd0lCQURDQ0FYQUdDU3FHU0liM0RRRUhBVEFlQmdsZ2hrZ0JaUU1FQVM0d0VRUU0zMlNvRisyZUI4S3ZKME03QWdFUWdJSUJRZjAxQlVRenBYM21qUzdPcHU5dThnVXB6MVFKRzl2SklMSGxXaEZuRy9ITDZ5VXkyeHBoOWVBK1pnMEN3ZXVrVWtmZXJPSmVJVHlwbmlvWDlXaHgweW9MdlZXMm9CcnpVemZVU2dlOGlkaVJicUNTaVdMU1BUclNnaWZYamZTaEdxRXlVQ2V2bVhndGRWWjFsSTU1RzQ1WGsxN3dtTDNUalB1VHR6WXh2S0R1Q2M3OXlUbDEvZ3J6Y2pmc0t0Y21ZYm5JbTc4M1RPRUJObElFWTRDZ0NrYmJkRkdadGtFRHpJRFhGeXFKSGJQY3h6SHJIZzd0emg0Qk52UkNrdzJlRlVLYkczYm10VmhBdHhpblNUQm9HVllYYThKa0JVRXFCTk9XdE5oWk50NVN6VTdnMHBBbTd0QklhT2dxQlhFR2JrUWk5czFFRU1GVUIxRWRRU1kyOTkrUUt0ZUJMZUVYaGd0bzJ1OUNRajYxSWpWVGtMQTk2VGVIN0NOcWVBd3V5Z2Q4Z0dMdDdrbUFZTk1NWTMrQ3FtZlorVENZcm9xTDZjM0FRMzhJaS8xanNnPT0iLCJhbGciOiJSUzI1NiJ9.eyJpc3MiOiJzb3JhY29tLmlvIiwiYXVkIjoiT3BlcmF0b3IiLCJleHAiOjE1Njc3NjQ2NTgsImp0aSI6ImRVM0FVdVJRX2xhM1V4WmF1bVRKWlEiLCJpYXQiOjE1Njc2NzgyNTgsIm5iZiI6MTU2NzY3ODEzOCwic3ViIjoic29yYWNvbSIsIm9wZXJhdG9yIjp7ImNvdmVyYWdlVHlwZXMiOlsianAiXSwicGVybWlzc2lvbnMiOlt7InN0YXRlbWVudHMiOlt7ImVmZmVjdCI6ImFsbG93IiwiYXBpIjpbIioiXX1dfV0sImFjY291bnRUeXBlIjoiMCIsInBheW1lbnRNZXRob2RTdGF0dXMiOiJyZWdpc3RlcmVkIiwib3BlcmF0b3JJZCI6Ik9QMDA4MTE4NTA0OSIsImNvdmVyYWdlVHlwZUF0dHJpYnV0ZXMiOnsianAiOnsidGVybXNWZXJzaW9uIjoiMSIsInBheW1lbnRNZXRob2RTdGF0dXMiOiJyZWdpc3RlcmVkIiwiY29udHJhY3RzIjpbXSwiY29udHJhY3REZXRhaWwiOnt9fX19fQ.ZGAPsSXHtVE5qd15VMtfBMFeIZjo1kfZuFM6hnUDj5WkBIJO8EBvRSdNZkBsLzc47HBsmsqB7x4jBzeDl8wh4xwGBJRNtI-_tlhjnbD5BlV6dXIIfpIzQsdGdCqjiksUjZOCXpo1FzzVqvprFpcorP9dovHg66oQ3fBU6-5J_Zm_iT8bozV9QOEgDWOSRll0bJtXkR2jHmWHoQjvyUaLez2w31u_JbkxlxZQ8HoQYrxpNPRtZI9mOJqLKsQyag2BeT6sV0tbu_kF_mrV82mGZYv0LLD_PEthA8IE_lFJk5bF8jYV47XybIRwwScjCpVtm1Xu8c4d0U7CAc2ehcbhyg' \
  -d '[
    {
      "tagName": "name",
      "tagValue": "CustomerMngt"
    }
  ]' \
  'https://jp.api.soracom.io/v1/subscribers/440525060023501/tags'

{
  "imsi": "440525060023501",
  "msisdn": "812025372219",
  "ipAddress": "10.134.233.97",
  "operatorId": "OP0081185049",
  "apn": "soracom.io",
  "type": "t1.standard",
  "groupId": "7300d51b-8145-44f6-b644-335ccf41834d",
  "createdAt": 1563786879213,
  "lastModifiedAt": 1567685079562,
  "expiredAt": null,
  "registeredTime": null,
  "expiryAction": null,
  "terminationEnabled": false,
  "status": "active",
  "tags": {
    "name": "CusntomerMngt",
    "CustomerMngt": "1"
  },
  "sessionStatus": {
    "lastUpdatedAt": 1567684521983,
    "imei": null,
    "location": null,
    "ueIpAddress": null,
    "dnsServers": null,
    "online": false
  },
  "imeiLock": {
    "imei": "866425033400716"
  },
  "speedClass": "t1.standard",
  "moduleType": "nano",
  "plan": 0,
  "iccid": "8981300025200020011",
  "serialNumber": "8981300025200020011",
  "subscription": "plan-KM1",
  "createdTime": 1563786879213,
  "expiryTime": null,
  "lastModifiedTime": 1567685079562
}
```


## /orders

```
curl -X POST \
  --header 'Content-Type: application/json' \
  --header 'Accept: application/json;charset=UTF-8' \
  --header 'X-Soracom-API-Key: api-3904e648-dd53-447d-b2e9-927e320dcb8e' \
  --header 'X-Soracom-Token: eyJraWQiOiJBUUVDQUhnYmdGdnFrclRTbGlNVmNCQnV0VXlVcnNvU1RqTTM4NlR5WGVsaEdlUWtOd0FBQVk0d2dnR0tCZ2txaGtpRzl3MEJCd2FnZ2dGN01JSUJkd0lCQURDQ0FYQUdDU3FHU0liM0RRRUhBVEFlQmdsZ2hrZ0JaUU1FQVM0d0VRUU15MVM1L1lyeFdtN3NnWTJGQWdFUWdJSUJRVUtLejlTUUduNzQ0ZjU0RzF2L3l3TVhVaktjSXVxdWlSVlozMzRUZnMybVpWRTVYMjlCdGl1NmY1YThyVFdhMGlLK0YvWG5oWmo0OHRXY0QyUWlnM29ENVArM0llck1kQnF6Rk5SZllGdVZpekxXcXBzdGNNOHdQb2EwVG5uUW9xVzRsQWpLYVA2SnhlZXA0VXVCV1RtNVZYdExJZFNnNk9HQWlXcnNVWW16ZVh0L1FHQmFSL1ZIOFZpV0hhZ1ptSmFsZThKWHUzRVk4SDNyODViNVh3OHdsOTdiRy9MQkFuTGdWZ1R0RWZlMy9vSzBENENXeXozc3pzbDVpVUF2bjg0SVkzN0dXZU9wZXVCc09kUWVHY3hnRG8yM1JJRXRQb2E4aDBKdHQ1dFVTTzl1R3Zkb28zT3RPOG1zd1pYT0ZlMDhrOHV6YmFhVURGNnJ2VHlVZGtrUE9TMWhyc1ZGc2lSSjQzQVJwSTdQQ1NDNTRVZFpNMWhLMk8yM0lnY0pkNFM3ZDBvMUFLRTRHZGhCbnhTZUd0VFNjcGd6aWxKajYreHptSVlQNWZkTUJ3PT0iLCJhbGciOiJSUzI1NiJ9.eyJpc3MiOiJzb3JhY29tLmlvIiwiYXVkIjoiT3BlcmF0b3IiLCJleHAiOjE1Njg4MDQxNDAsImp0aSI6Il9XaVlCMmUwc2VLN0w1OXktZkR5N0EiLCJpYXQiOjE1Njg3MTc3NDAsIm5iZiI6MTU2ODcxNzYyMCwic3ViIjoic29yYWNvbSIsIm9wZXJhdG9yIjp7ImNvdmVyYWdlVHlwZXMiOlsianAiXSwicGVybWlzc2lvbnMiOlt7InN0YXRlbWVudHMiOlt7ImVmZmVjdCI6ImFsbG93IiwiYXBpIjpbIioiXX1dfV0sImFjY291bnRUeXBlIjoiMCIsInBheW1lbnRNZXRob2RTdGF0dXMiOiJyZWdpc3RlcmVkIiwib3BlcmF0b3JJZCI6Ik9QMDA4MTE4NTA0OSIsImNvdmVyYWdlVHlwZUF0dHJpYnV0ZXMiOnsianAiOnsidGVybXNWZXJzaW9uIjoiMSIsInBheW1lbnRNZXRob2RTdGF0dXMiOiJyZWdpc3RlcmVkIiwiY29udHJhY3RzIjpbXSwiY29udHJhY3REZXRhaWwiOnt9fX19fQ.E2ecZb59kWj46uHOt21A8d0HXgJbljJEo44FkiXQCqG6qC0HUUwRicjcwIyL3GFGB5iKtnpQzvyCwwVSUF29exrXiPHGAHgLBeefLnTtF0WeBa5L3XrYVFNgyNKBTXS2CsRTyanj3IO4ytn9ulAJtA3pgFeoLSfBJ5umNCA20kuExr7jsd4eUCmdJP22OdOdtBVfX6ooDGcLYX2j_ini4AfvcEvqfqT_PJiZxuw5DWaDWq-vXl7zNq1pLZIwknyToY5BPLpCFaxnX4M-dc7JVtZ7dmQbuhGbBAMbHIAJykekzzynWV33RhYpFNtCTNrs8YRQEG9hKWdUvaBCVZgKLg' \
  -d '{
              "orderItemList": [{
                  "productCode": "4573326590273",
                  "quantity": 2
              }],
              "shippingAddressId": "c300add2-9844-4ab4-a1a6-30145340d856"
          }' \
  'https://jp.api.soracom.io/v1/orders'
  
{
  "orderId": "20190917111839_104fe841",
  "orderItemList": [
    {
      "product": {
        "productCode": "4573326590273",
        "productName": "SORACOM Air SIM card  plan-KM1  size:Nano(for data) 1 SIM pack1",
        "description": "This type of SIM provides cellular LPWA (LTE Cat. M1) connectivity. NOTE: Please be aware that communications charges for this type of service are significantly higher than for normal service. Cannot be used with regular LTE devices.",
        "count": 1,
        "price": 1500,
        "currency": "JPY",
        "properties": {
          "contractType": "no_sms",
          "simSubscription": "plan-KM1",
          "simSize": "nano"
        },
        "productType": "sim",
        "productInfoURL": "https://soracom.jp/products/sim/plan-km1/",
        "productImageURLs": []
      },
      "quantity": 2,
      "productAmount": 3000
    }
  ],
  "shippingAddressId": "c300add2-9844-4ab4-a1a6-30145340d856",
  "shippingAddress": {
    "countryCode": "JP",
    "zipCode": "141-0022",
    "state": "東京都",
    "city": "品川区",
    "addressLine1": "東五反田 1-10-8",
    "building": "五反田S&Lビル 8階",
    "companyName": "株式会社CAMI&Co.",
    "department": "IoT Platform",
    "fullName": "神谷雅文",
    "phoneNumber": "03-6417-9399"
  },
  "shippingCost": 907,
  "taxAmount": 240,
  "totalAmount": 4147,
  "email": "iot_dx_soracom@cami.jp",
  "currency": "JPY"
}
```


## getBilling: /bills/{yyyyMM}

```
curl -X GET \
  --header 'Accept: application/json' \
  --header 'X-Soracom-API-Key: api-c877254a-35e2-4e03-819d-d7f2588e22f7' \
  --header 'X-Soracom-Token: eyJraWQiOiJBUUVDQUhnYmdGdnFrclRTbGlNVmNCQnV0VXlVcnNvU1RqTTM4NlR5WGVsaEdlUWtOd0FBQVk0d2dnR0tCZ2txaGtpRzl3MEJCd2FnZ2dGN01JSUJkd0lCQURDQ0FYQUdDU3FHU0liM0RRRUhBVEFlQmdsZ2hrZ0JaUU1FQVM0d0VRUU0zMlNvRisyZUI4S3ZKME03QWdFUWdJSUJRZjAxQlVRenBYM21qUzdPcHU5dThnVXB6MVFKRzl2SklMSGxXaEZuRy9ITDZ5VXkyeHBoOWVBK1pnMEN3ZXVrVWtmZXJPSmVJVHlwbmlvWDlXaHgweW9MdlZXMm9CcnpVemZVU2dlOGlkaVJicUNTaVdMU1BUclNnaWZYamZTaEdxRXlVQ2V2bVhndGRWWjFsSTU1RzQ1WGsxN3dtTDNUalB1VHR6WXh2S0R1Q2M3OXlUbDEvZ3J6Y2pmc0t0Y21ZYm5JbTc4M1RPRUJObElFWTRDZ0NrYmJkRkdadGtFRHpJRFhGeXFKSGJQY3h6SHJIZzd0emg0Qk52UkNrdzJlRlVLYkczYm10VmhBdHhpblNUQm9HVllYYThKa0JVRXFCTk9XdE5oWk50NVN6VTdnMHBBbTd0QklhT2dxQlhFR2JrUWk5czFFRU1GVUIxRWRRU1kyOTkrUUt0ZUJMZUVYaGd0bzJ1OUNRajYxSWpWVGtMQTk2VGVIN0NOcWVBd3V5Z2Q4Z0dMdDdrbUFZTk1NWTMrQ3FtZlorVENZcm9xTDZjM0FRMzhJaS8xanNnPT0iLCJhbGciOiJSUzI1NiJ9.eyJpc3MiOiJzb3JhY29tLmlvIiwiYXVkIjoiT3BlcmF0b3IiLCJleHAiOjE1Njc3NzIyMjIsImp0aSI6ImdZeTg2RTJsYUNkMGF4WjVuZV96Y1EiLCJpYXQiOjE1Njc2ODU4MjIsIm5iZiI6MTU2NzY4NTcwMiwic3ViIjoic29yYWNvbSIsIm9wZXJhdG9yIjp7ImNvdmVyYWdlVHlwZXMiOlsianAiXSwicGVybWlzc2lvbnMiOlt7InN0YXRlbWVudHMiOlt7ImVmZmVjdCI6ImFsbG93IiwiYXBpIjpbIioiXX1dfV0sImFjY291bnRUeXBlIjoiMCIsInBheW1lbnRNZXRob2RTdGF0dXMiOiJyZWdpc3RlcmVkIiwib3BlcmF0b3JJZCI6Ik9QMDA4Njk4NzUyMCIsImNvdmVyYWdlVHlwZUF0dHJpYnV0ZXMiOnsianAiOnsidGVybXNWZXJzaW9uIjoiMSIsInBheW1lbnRNZXRob2RTdGF0dXMiOiJyZWdpc3RlcmVkIiwiY29udHJhY3RzIjpbImxhZ29vbiJdLCJjb250cmFjdERldGFpbCI6eyJsYWdvb24iOnsicGxhbiI6Im1ha2VyIiwidmlld2VyTWF4TGltaXQiOjIuMCwiZWRpdG9yTWF4TGltaXQiOjEuMCwiYWxlcnRNYXhMaW1pdCI6MTAuMH19fX19fQ.dNtTeHmtSuiZFVZM_w0S3_EefWGgBs-y788uAqkAEs8UgreDUIVn1rG7gHBCHVumNoCIIw9QVsFDG-GE6vyDAfmz5oK9C_f_WUeJRfVIuNt4Y-1c_gJ3lUOpPgFdVQ3n9KCSvc5F7U6kZkULO4ZqiBOeqf8DbezYgvYc1NZVVyh_zId7w8VrFdlQRatylaYL0Ne7vjPCjmfh_6ukaCUhL-e_1XKwP1jk3YFsKp_Lt5XUEVVD_zS98w6vsOJvyeAczUtiEARboQXrv9di7vP3eXBMkURSSejQET03rpbMVmGMylgandV2dGEi0EQYqbFBP2lpnKh4E8Z2yg_0vJHyQg' \
  'https://jp.api.soracom.io/v1/bills/201908'

{
  "yearMonth": "201908",
  "amount": 13203,
  "state": "closed",
  "paymentStatus": "paid",
  "paymentTransactionId": "20190903033613626_84ed364c-de87-4c0f-b12a-435f0c23c59b"
}
```


## /bills/{yyyyMM}/export

```
curl -X POST \
  --header 'Content-Type: application/json' \
  --header 'Accept: application/json' \
  --header 'X-Soracom-API-Key: api-3904e648-dd53-447d-b2e9-927e320dcb8e' \
  --header 'X-Soracom-Token: eyJraWQiOiJBUUVDQUhnYmdGdnFrclRTbGlNVmNCQnV0VXlVcnNvU1RqTTM4NlR5WGVsaEdlUWtOd0FBQVk0d2dnR0tCZ2txaGtpRzl3MEJCd2FnZ2dGN01JSUJkd0lCQURDQ0FYQUdDU3FHU0liM0RRRUhBVEFlQmdsZ2hrZ0JaUU1FQVM0d0VRUU1uRWdLVlRiZGFsbWd4RGtkQWdFUWdJSUJRZlhXR1k1UHdqUjN4ZWY5SHhuZVo4NzN3THVHN3kzblY1TkZnTFZkNFdTaEdONTJBa1ZaVG55dG80RGY2UXVJWm9BS05KbFNqZWcyWnowRjV1S1p3amI0cy9pQlNCQno0bnZhcHdYQ0dOOFNjNHVMYVNKOUMzc2g3bmxFUFlSeTJRRHBCalhrL1BZNHpwbkYzQklRN3pQeXVKcmlqR0dwTmFDT3c3cXl2bGgwSXY0UVUzL0pmMFRWbUxteWlObEJLNVpMN25EV0JwZk1KUlJ5elVXZ2dxMUFYMXp1dndpV01KREZjMmVST0pOdkpxdXZ0TlR1M01sUm5RL29JOVBQWGNWdFhETFY3NEZMRVF3bWlmTUVhZVBxRzhvSjlQcnZmSlRMTnN1Q0xPYnMxVVI4dGU0eTJxS2xDQzFacVdYVitCWGM0WXROREhBbzNoN2xEbnVIOGRuUEozUjc0Z3dNcWE3L0dodjNUSWt1VlFmYzV0VDF4L25RR2pOdkZFVHZ2L1k3SWRsdkdsSU9BdE1UT09TRkRUWFNXZTVBN2I5T1pPU0Z4MTJZSjNxMHdnPT0iLCJhbGciOiJSUzI1NiJ9.eyJpc3MiOiJzb3JhY29tLmlvIiwiYXVkIjoiT3BlcmF0b3IiLCJleHAiOjE1Njc3NzIyODksImp0aSI6IkpaOEdrY1R2c2VFcGVWQ3pCQTBLcFEiLCJpYXQiOjE1Njc2ODU4ODksIm5iZiI6MTU2NzY4NTc2OSwic3ViIjoic29yYWNvbSIsIm9wZXJhdG9yIjp7ImNvdmVyYWdlVHlwZXMiOlsianAiXSwicGVybWlzc2lvbnMiOlt7InN0YXRlbWVudHMiOlt7ImVmZmVjdCI6ImFsbG93IiwiYXBpIjpbIioiXX1dfV0sImFjY291bnRUeXBlIjoiMCIsInBheW1lbnRNZXRob2RTdGF0dXMiOiJyZWdpc3RlcmVkIiwib3BlcmF0b3JJZCI6Ik9QMDA4MTE4NTA0OSIsImNvdmVyYWdlVHlwZUF0dHJpYnV0ZXMiOnsianAiOnsidGVybXNWZXJzaW9uIjoiMSIsInBheW1lbnRNZXRob2RTdGF0dXMiOiJyZWdpc3RlcmVkIiwiY29udHJhY3RzIjpbXSwiY29udHJhY3REZXRhaWwiOnt9fX19fQ.ZSyKZFY3UQ_YDI3FP4RXoO7-CfhVefecdIHaMcCYv-zGJaJcnoJPGqn_697BRSgTw6MKjTyzLofiiK1T4rULEMlFaD618L_1XA-a1OJmQ3IIbZ4PbObQfPMPPrVjWGb6XwTuTO-GkssiEWRV5D5bMcZfAl8TIgyTRi8LazPGXuRHZIsMcfkk5tCzHzgYCNUKPDGY0rHPFNQ2_lR45l9Fb6ZVdae4Ncuq0Y5GBlw2Inqss4nIJgvYZo8cEoHmJhIYBP_nTscIAMVxSXON89NqzK4-8UFUqycj0pMDM0Y24hWfO5ViO4VN6_1Gf-QMPLSmIB2GUXS8nA6FixW3vdvLJw' \
  'https://jp.api.soracom.io/v1/bills/201909/export?export_mode=sync'

{
  "url": "https://soracom-billing-fileoutput-prod.s3.ap-northeast-1.amazonaws.com/20190905121833-OP0081185049-billing-201909.csv?X-Amz-Security-Token=AgoJb3JpZ2luX2VjEIz%2F%2F%2F%2F%2F%2F%2F%2F%2F%2FwEaDmFwLW5vcnRoZWFzdC0xIkYwRAIgRpMxcZ0dH8I2XLLOq%2BN0kpYPYrKLVMx%2BWAYGeuV%2BWuICIBV6kHOAqzqvXjlNXG2%2Fak23laDBnRE7uFQMsMGzypGFKuQDCEUQABoMNzYyNzA3Njc3NTgwIgxJULINUA%2BJ3cHTqegqwQPEInm9duBNhkYRzRZvYWP1iPQPpkwRxVVs0QpT2V62kbKXGJCDvtkZ1uVI5RVo7GvEOv%2Bp0rNBjd9gHBwuC0v%2B4r9kEURup1xfeSD1OXxjnW8eScWbMaOYKJu%2Fia0n5kqODMXjoBL%2FB4NLF%2F%2BDadjfn%2FFadV4ZN8SyaCQZXlYzLKNaSy87nq6n03x1WYgOuK6QtDlsnbsAQHJ1zIcLll6kd8Vny%2BriXTKis9MXWmoZoi65useUTVpwXUtqArhKonpjQPOj4Cg6oTZYh47Kjd164B3%2B6jiDSGSZTJieFuQC%2F86rlA7Ng1g94AoQaD1f%2BifcBufghweRqE0F8LZbGCZrSoIinxun3iw959trMUI1r0pyuPHZxhEc5Y7a%2BBpGQZxnM78DE9ifurDcALCIc4nOrNe6t3HR0obtXOmLSW8yd4pbypbou4jMiu%2BZFExvys3o5yz4YHFCCwGmNK4YLyLcMITT4cyTNSG32XigVPH32YE5qwXGkrb%2FnXQ3vVX84wNbBpAFsH8E5w0gQADbI7HBIk0FYlzwOawdKxXzrRBuC%2BfZJrSQbmYagTd6NklNckqF2bJWqZw9Xrl%2BRhYkkoo%2F1TDu6sPrBTq1ATzKRBoyzrdK%2BinR5vLL9GfrSfkXR8ZkwzAWPty5UW%2F5TLMogZDk9BXXiIpc25EeIIAtQyudVvn9jA8J5Qj5dcPj9GnQCWYkdknZfrzSOZk7KQvgNg34VkREaTYEINHmEt6mzyDT%2FNfc2uGm2iBaAqKBOQXNKjFcleaK53DxXaYTrchC%2FzTSwWdeNXl%2BJUb7bnl5%2FehKL%2BT4FYS1EMebCgjeGaH0V2XHNE7Es8SO5cZhKHlbSmM%3D&X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Date=20190905T121833Z&X-Amz-SignedHeaders=host&X-Amz-Expires=172800&X-Amz-Credential=ASIA3DFHLSGGPCLXLCE5%2F20190905%2Fap-northeast-1%2Fs3%2Faws4_request&X-Amz-Signature=7aeddaded8f0fee725225c9a3c8b8685cad67e1396764aca69061970d470a760"
}
```

[Billing](../Invoice/20190905121833-OP0081185049-billing-201909.csv)



















## /auth/password_reset_token/issue

```
curl -X POST \
  --header 'Content-Type: application/json' \
  --header 'Accept: application/json' \
  -d '{"email": "iot_dx_soracom@cami.jp"}' \
  'https://api.soracom.io/v1/auth/password_reset_token/issue'

no content
```

## /auth/password_reset_token/verify

```
curl -X POST \
  --header 'Content-Type: application/json' \
  --header 'Accept: application/json' \
  -d '{"token": "3adeb0f5-a0f5-4c95-a2c0-8009ad9b85e6-275c3528-6a28-4035-88ab-a7fd31cd2462", "password": "CAMI333cami"}' \
  'https://api.soracom.io/v1/auth/password_reset_token/verify'

no content
```