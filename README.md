# 專案名稱 : 學校專題 - 打靶系統

開發環境 : Arduino IDE(硬體控制) . VS(網頁前端)

組員 : 110810549 鄧筌祐 . 110810551 許嘉烜

![70](https://user-images.githubusercontent.com/36965820/149462050-26af5bb2-7412-4793-ba1e-4193f72008a3.jpg)


## Arduino程式簡介:

### 程式分為兩種類型:

1.硬體感應&控制
  ![72](https://user-images.githubusercontent.com/36965820/149460996-b9d64cfd-7ccb-4862-afc6-314f23bbea8d.jpg)


2.WiFi & MQTT(一種IoT間的通訊協定)連接

實際上的MQTT伺服器是用PC架設在同一個WiFi底下 . 不使用外網的公開伺服器
  ![71](https://user-images.githubusercontent.com/36965820/149461015-688cddfc-237c-4f31-b4c3-c3aa66c91550.jpg)

實際上要寫入的實體有:

1.標靶本體

* 工作內容 : 接收MQTT指令 > 硬體計分 > MQTT回傳分數

2.遙控器

* 工作內容 : 接收來自電腦的串列埠指令 > 發送MQTT指令 > 接收MQTT分數 > 用串列埠回傳電腦

### 網頁程式簡介:

1.主頁面

* 工作內容 : 所有人都看的到的打靶網頁,分頁有影片示範、射擊要訣、關於我們、登入

![image](https://user-images.githubusercontent.com/55796905/149460904-b6a21452-efd1-4095-8ca1-e686d08629ce.png)

![image](https://user-images.githubusercontent.com/55796905/149460923-483dc072-fd9e-4051-bb36-62cbcfbd8318.png)

![image](https://user-images.githubusercontent.com/55796905/149460796-7e57d0ee-520e-4041-a77b-ead8ea305755.png)

2.登入後的主頁面

* 工作內容 : 打靶系統內的人員透過帳號密碼登入後的頁面,分頁有打靶成績、更改密碼、郵件驗證、登出

![image](https://user-images.githubusercontent.com/55796905/149463086-22c22f0a-2eef-4bc0-8a40-f72f55f0fac5.png)

![image](https://user-images.githubusercontent.com/55796905/149463123-726ce4a2-2b55-412d-acc6-e2ddd475c41e.png)

![image](https://user-images.githubusercontent.com/55796905/149463049-4b71731c-d4ce-43dd-a87d-a7d94f7c1416.png)

# 參考資料

[網頁模板](https://templatemo.com/about)
