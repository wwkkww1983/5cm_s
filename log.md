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
+ 今日无进度更新

## 2018-04-19
>Recorder: WilliamMy
+ 读取ADC部分文件添加
+ 
## 2018-04-21 (With 0420)
>Recorder: YTom
+ 周五因为405封闭，所以我们把车拿出来了，在梁厶宇那里
+ 周五下午以及今天晚上我们简单地调了一下车，大致顺序如下：
>   * 1. 把各个功能模块放进主工程，并测试
>   * 2. 测试程序主体逻辑（时间控制和模式切换）
>   * 3. 测试PID下的速度控制
>   * 4. 将Kalman滤波结果传给PID产生速度输出（暂不考虑速度环）
>   * 5. 非道路测试：在非道路运转模式下，人为改变小车姿态能产生速度输出，且满足一定控制规律（偏差大则输出速度大）
>   * 6. 在前一步基础上实现平衡功能
+ 总体情况：程序逻辑和模块基本没有问题，主要问题在车子上的；因为新增电池问题，目前进度只达到第3步。
+ 问题：
>   * 1. 驱动板可能存在小问题（接线不牢和某个元件存在问题），导致一侧电机始终难以转起来，然而因为405问题，暂时没有工具解决；
>   * 2. 另外今天发现之前顺出来的电池没电了，最近也没法充电；
>   * 3. 可以说目前工作处于停滞状态。
+ 关于修改：
>   * 1. 修改display，以小字号显示（一面8行），因为显示内容多，所以提高一下显示效率,另外存在电机运动花屏现象（同时工作，未停止屏幕更新），考虑是中断干扰，但是看不到电机反馈还是很不方便啊；
>   * 2. 将main的初始化和循环部分做了部分拆分，一些内容封进函数里，简化代码，方便阅读；
>   * 3. 改变了一些按键检测的结构，今天发现按键效果有限，尤其是两个按键同时按下的动作（可能因为程序更复杂了，按键效果变差了），所以打算让按键动作尽可能简单，或者直接废弃（具体我再看看）；
>   * 4. 大部分变化应该是肉眼可见的那种，其他细枝末节的改变并不重要就不细说了，我的程序在成功运行前都会在ytom_t分支里。

## 2018-04-23
> by Shine Wong
+ 感觉思路非常清晰了！车队的问题的确比较无奈，驱动板的话不妨在淘宝上先买个驱动板凑合用，就一般几块钱的。
+ 关于中断的话，问了一下一个寝室的电院博士emm......他说只要中断程序的运行时间不长一般是问题不大的，然后可能需要设置一下中断优先级的问题，具体我也不是很清楚其实，还是看具体的功能是一个全局控制的还是局部的，然后来设置，试试吧嗯
+ 随便看了一下代码，对代码结构非常满意~厉害厉害

## 2018-05-05
>Recorder: lsy
+ 单纯PD调节，P=9,D=22有较小能力平衡，但逐渐拍地。加入速度控制后，原有PD不变情况下车模拍地更严重
+ 老曹说似乎应该把车模底盘和杆的角度减小，即成V形。明日决定尝试改变机械结构
+ 前瞻电感电压过小是由于黑色电感没有并联6.8nF的电容，更换蓝色电感后测得放大电压最大2.2V。但显示屏上ADC读值很飘（不排除是电感问题）

## 2018-05-06
>Recorder:My
+ PD调节，发现D的影响不尽如人意。速度环的P=20时造成车在平衡位置附近疯狂抖动。
+ 学长说可以设置倒向前方时的P比倒向后方的P更大，让车一直保持往前ps:我觉得是倒向后方的P更大才能向前

## 2018-05-08
> Recorder: YangCx
+ Prof. Wong 发现，我们的程序将调节目标值错误地储存在了陀螺仪中值（gyroMid）中，使得卡尔曼滤波值与实际角度相差约17度。
+ 将与 gyroMid 相关的程序修改，并调节了 PID 值之后，小车原有的拍地和抖动现象均有减轻，在运行起始阶段可以比较平稳地运动一段时间，之后的情况依然不理想。
+ 当前 PID_pos_p = 10, PID_pos_i = 0, PID_pos_d = 0, PID_spd_p = 14, PID_spd_i = 6, PID_spd_d = 0.

## 2018-05-09
> Recorder: My
+ Prof Wong 发现PID控制算法中，算出的值应当是速度的变化量，而不是速度的当前值。
+ 家什搬到了二楼。
+ 目前的车能在平衡位置左右晃一会，但是稍微偏转大一点就救不回来。
+ 当前 PID_pos_p = 12, PID_pos_i = 0, PID_pos_d = 44, PID_spd_p = 15, PID_spd_i = 0, PID_spd_d = 0.

## 2018-05-10
> Recorder: 严汉三
+ 安排了一下小组事宜
+ 赛车相关高级零件购置和解决主板驱动板的问题:梁厶予
+ 更换kaputt光编:严川和杨晨曦
+ 焊接赛车前瞻板和调试前瞻程序:方继冲
+ 解决通过前瞻定位赛车的问题:莫庸 
+ 赛车调试:杨涛  
+ 今日调车成果：小车太狡猾，一朝回到解放前，稳定性能进度倒退十年。

## 2018-05-11
> Recorder: Mycroft
+ 光编已找到
+ 前瞻板除部分电容缺货已基本焊好
+ git上需要补充“project.h”

## 2018-05-12
> Recorder: 严汉三
+ 待解决问题
  - 给电机占空比后卡尔曼滤波波动变得很大//wong
+ 程序
  - 对卡尔曼滤波值求取mean来优化程序//Wong 
  - 选择正确的陀螺仪输出通道，对原有错误程序进行更改//wong
  - 解决滤波角突变问题//wong
  - 修改程序中关于Gyromid的错误（详细见备注）//yan and wang
+ 硬件
  - 光编安装及性能检测//yan and yang
  - 焊制前瞻板及初步测试//方继冲
  - 开始新主板PCB的设计//梁厶予
+ 场地实操
  - 回到smooth状态：经过上述程序优化中部分修改（yan and yang部分）之后，小车初步能smooth站立3秒钟左右，PID参数参考之前参数。//yan and yang
+ 经验
  - 电池没电会影响陀螺仪的读数准确性 
+ 备注
  - 关于Gyromid的程序修改记录
remove the "//" of get gyromid
add "//" to  gyromid = 0
```cpp
sendSpeed[0] = PIDcalc(&PID_Posi[0],GyroMid,KalmanAngle); // GyroMid should be replaced by TargetAngle
```
TargetAngle should be defined first and should be give the value of the original value of KalmanAngle

## 2018-05-13
> Recorder: Wong
+ 先写写上午做了啥，因为下午晚上可能不来了.....
+ 完成了最小核心板的主板的原理图，还需要梁厶予再校验一下
+ 在昨天川哥和晨曦程序的基础上进行修改，(我是觉得改的结果和我前几天的程序差不多，但是这般程序显示屏也不画了，滤波也稳了，整个车都牛逼了很多)，放在了`更丝滑的程序`这个文件里面。此外还做了些小的修改，就不写出来了(我也忘了)
+ 注意事项的话，开机后记得看看陀螺仪角速度值是否准确，就是在静止状况下其值是否<5，比较大的话原因可能是开机的时候受到了振动，所以读到了一个角速度，静止重新开电源就行了。
+ 今天还要大家完成事情：
  - 前排电感的安装与测试
  - 电感安装好后测试莫庸写好的getX()这个程序，并且将值显示在显示屏上。这个过程之前可能需要标定一下各个电感，调节滑动变阻器，使他们在相同点读值相同
  - 继续调试平衡的pid参数
  大家各自对号入座找自己的任务吧

> Recorder: Mycroft
+ 小车现在可以保持直立了，当前 PID_pos_p = 11, PID_pos_i = 0, PID_pos_d = 480, PID_spd_p = 15, PID_spd_i = 0, PID_spd_d = 0.
+ 新前瞻板测试完毕，应该可以使用。
+ 前排电感安装完毕，但是还没和前瞻板进行连线测试。

## 2018-05-14
> Recorder: 严汉三
+ 小车前部电感/电容正在安装ing：电感接线焊接完毕-方继冲
+ 新PCB前瞻板设计ing-梁厶予
+ 速度环PID和角度平衡环PID构思：目前准备通过给车一个向前偏的倾角来控制速度-汪绪衡

## 2018-05-15
> Recorder: YangCX
+ 已成功读取电感值。显示电感值和计算偏差X都进行了一半。-莫方
+ 画好了新主板。-梁
+ 速度环控制已整合进程序但调试失败，进入行驶模式后电机快速转动并瞬间停车。顺手解决了原更丝滑的程序电机反转函数传入参数错误导致无法反转的bug。方向环写了算法，还未整合进程序。-杨严
+ 发现十根连接电感的线中的一根被卷进了车轮里，同志们再焊一根吧。线路复杂，布线的耐操性还有待提高。

## 2018-05-16
> Recorder: MY
+ 电感的线已经焊好，获得车在赛道上位置的函数GetX()可以得到值。发现前瞻板上滑动变阻器对读到的电压最大值影响几乎没有，没能标定各个电感的值。
+ 速度环方向环整合。考虑错开调车档期。

## 2018-05-17
> Recorder: lsy
+ 经测试发现前瞻板正常，昨日出现的问题可能是因为扭的电位器和所测AD口没有对应。但未进行标定
+ 小车走线杂乱易松动，待解决
+ 汪更新了丝滑板程序
+ 杨严二人来实验室研究速度环。注意跑车前接好前瞻板。逮了切换行驶模式处程序flag被注释的bug。行驶模式只开平衡环时还没问题，速度环还要调。

## 2018-05-18
> Recorder: undefined
+ 基地切换至二楼。研究了气球打气筒的工作原理。
+ 新增通过改变目标角度实现速度环的方案，与原方案并行调试。在行驶模式显示当前占空比、光编读取的转速，试图找出真相，将速度环调整到正确运行。

## 2018-05-19
> Recorder: undefined
+ 据说光编读数有问题。

## 2018-05-19
> Recorder: Shine Wong
+ 光编问题解决，并且读取光编的程序也有所变化，现在在光编的中断里面不再读取CNT寄存器的值，而是记录脉冲数，由pit时钟来获得，详情可见程序 --by YTom
+ 中断程序思路测试:尝试把所有主要操作都放在中断里面，主程序里面几乎不放操作，以失败告终，可能是因为中断内时间太长--by YTom
+ 光编问题解决后顺便速度环也不会乱转了，测试了一下，目前可以向前跑但是波动很厉害，并且不能达到设定的速度目标值。设想是平衡环调的太好的缘故，稍有一点角度变动就给了较大的控制量，于是把速度控制给抵消了。考虑减小平衡环的P，让加速更加平滑
+ 可能还是需要再搭一辆车
+ 接下来的工作：
    - 我和杨涛调节速度环
    - 莫庸和方继冲还有梁厶予调节方向环，可以到405的赛道那里调，只需要把小车平衡的目标值放的前倾一点它就会往前跑了
    - 川哥和杨晨曦调节角度思路的速度环
    - 此外之前说的各自的工作还是得继续做啊，板子啥的也得焊了
    - 关于搭新车的事情再说吧

## 2018-05-23
> Recorder: lsy
+ 方继冲焊好了新主板，测试可用；
+ 前瞻板上电感的线断了一根，请温柔对待它们（待改进）；
+ 第四个电感的读数最小值300，比其他0到100的值大了很多，原因待查；
+ 电池都没电了；
+ 方向控制和速度控制中，电机快速正反转，产生很大噪声，程序问题；
