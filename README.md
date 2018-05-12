# 5cm_s

## 项目组织方式
+ KBITest 文件夹作为整个项目主体文件夹，经过测试的程序均在其上进行添加修改
+ 对某些模块单独进行测试时可以另外创建一个分支(branch), 或者clone到各自的本机上进行运行。测试通过后再push到github上。
+ 应保证KBITest总是可以直接运行的

## 关于项目文件夹的使用
+ 除去PROJECT文件夹外, KBITest中有四个文件夹,分别为CORE DRIVER LIB USER, 其分别包含由底层到上层不断封装与抽象化的文件, 通常相邻文件夹中的文件可以互相包含，而跨级文件夹中文件不能有包含关系(如LIB中文件不能include CORE中的文件),亦即面向对象中 `以保护方法继承`, 然而这里以每一个文件作为一个类的单位
+ 正常情况下,将整个项目文件夹(KBITest)clone到本机后，打开keil项目文件即可运行。但要注意相关外设引脚配置是否一致。
+ 在本机端, 项目文件夹可以用gitbash进行维护。确认提交后再在push到github完成修改。

## 关于协作方式
+ 在对项目进行修改前，首先在github上查看是否已经有提交修改，并clone到本机更新本机文件。
+ 对项目的修改可以包含任何形式， 如某个底层库配置错误，或者增加、优化功能，改变相应的端口引脚，添加新的文件等，甚至可以是对本文档错别字或语意的修改
+ 提交修改要确认项目文件运行无误，并写好commit的修改日志，说明做出什么样的修改以及原因
+ 每天需有一人完成当天的工作日志并commit

_copyright: 同济大学Tu_smart智能车队版权所有_

## Record of this modification

remove the "//" of get gyromid

add "//" to  gyromid = 0

```cpp
sendSpeed[0] = PIDcalc(&PID_Posi[0],GyroMid,KalmanAngle); // GyroMid should be replaced by TargetAngle
```
TargetAngle should be defined first and should be give the value of the original value of KalmanAngle

