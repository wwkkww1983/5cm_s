# Working Log
`未尽事宜，请各自添加`

## 2018-04-14 (Append on 04-15)
>Recorder: YTom
+ 测试用车搭建完成
+ 队长交代下一阶段工作安排
+ 我自己梳理了一下程序

## 2018-04-15 
>Recorder: YTom
+ None

## 2018-04-16
>Recorder: YTom
+ 测试光编和基于光编返回值的PID程序（失败，现在主要问题是OLED显示的光编读值总是少一个，而且轮子转的时候OLED花屏）
>Recorder: Shine WONg
+ OLED 花屏之前也遇到过这个问题，可能是因为OLED执行过慢，具体原因当时也没有去细加追究，后来完成了KBITest里面用的display的库以后就没有这种问题了，建议也直接沿用KBITest里面display.c .h的库文件试试。光编我不是很清楚换过没有，反正我们车上一个光编应该是坏的，在我寝室还有一个emm.....顺便把信号发生器也拿去车队吧
+ 以及这个工作日志也不是让亲爱的杨涛学弟一个人写的，调试平衡车的工作也不是让他一个人完成，只是让他统筹安排平衡车的调试事宜。希望各位有事没事也贡献一点代码。

## 2018-04-16
>Recorder: YTom
+ 昨天的花屏问题今天一来就没有了，感觉是硬件的问题（感谢马忆飞学长），而且我已经用的display模块了。
+ 今天把PID的程序测试了一些，达到了一些效果，另外增量式的PID我测试下来不知道有点什么的问题，效果没有实现，我改成离散PID可以使用。
+ 下一步我觉得等车搭完就可以试试平衡了。

## 2018-04-18
>Recorder: lsy
今日无进度更新