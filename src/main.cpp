/*
接线说明:无

程序说明:此程序用于演示如何使用ESP32s36来向www.example.com网站服务器发送HTTP请求并通过串口
         监视器将网站服务器响应信息通过串口监视器显示出来。

注意事项:无

函数示例:无

作者:灵首

时间:2023_3_16

*/
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiMulti.h>

#define URL  "http://www.example.com"   //是不能用等号的吗

WiFiMulti wifi_multi;  //建立WiFiMulti 的对象,对象名称是 wifi_multi



/*
# brief 连接WiFi的函数
# param 无
# retval 无
*/
void wifi_multi_con(void){
  int i=0;
  while(wifi_multi.run() != WL_CONNECTED){
    delay(1000);
    i++;
    Serial.print(i);
  }

}



/*
# brief 写入自己要连接的WiFi名称及密码,之后会自动连接信号最强的WiFi
# param 无
# retval  无
*/
void wifi_multi_init(void){
  wifi_multi.addAP("haoze1029","12345678");
  wifi_multi.addAP("LINGSOU12","123455678");
  wifi_multi.addAP("LINGSOU1","123455678");
  wifi_multi.addAP("LINGSOU234","12345678");   //通过 wifi_multi.addAP() 添加了多个WiFi的信息,当连接时会在这些WiFi中自动搜索最强信号的WiFi连接
}



/*
# brief  通过HTTP请求获取指定的网址的相关信息
# param  String URL_REQUESTED:对应的需要请求的网址
# retval  无
*/
void httpClientRequest(String URL_REQUESTED){
  //实例化,创建一个HTTPClient对象
  HTTPClient httpClient;    

  //通过 httpClient.begin()配置请求地址,可以只使用网址来设置请求
  httpClient.begin(URL_REQUESTED);
  Serial.print("URL:");
  Serial.println(URL_REQUESTED);
  Serial.print("\n");

  //使用GET()函数启动连接并发送HTTP请求,同时获取状态码'
  //根据状态码来进行下一步的动作
  int httpCode = httpClient.GET();
  Serial.print("send request to url!");
  Serial.print(URL_REQUESTED);
  Serial.print("\n");

  //根据状态码来进行操作
  //如果是200,则说明请求成功,则要求在串口返回请求payload的字符串
  //(就是从服务器获取响应体信息并通过串口输出)
  if(httpCode == HTTP_CODE_OK){
    String responsePayload = httpClient.getString();
    Serial.print("Serve response payload:\n");
    Serial.print(responsePayload);
  }
  //获取失败则输出错误的状态码
  else{
    Serial.print("serve response code:");
    Serial.print(httpCode);
    Serial.print("\n");
  }
  //关闭HTTP连接
  httpClient.end();
}




void setup() {
  //连接串口
  Serial.begin(9600);
  Serial.print("serial is OK\n");

  //wifi 连接设置
  wifi_multi_init();
  wifi_multi_con();
  Serial.print("wifi connected!!!\n");

  //使用HTTP连接获取信息
  httpClientRequest(URL);
}



void loop() {
}