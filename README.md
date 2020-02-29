# 缺陷检测系统v1.0

系统功能由**文件输入输出**、**图像显示**、**图像标注**、**缺陷检测**四部分组成。
## 系统总体框架
---
！[系统总体框架](https://github.com/kingbackyang/chip_detect/raw/master/imgs/structure.png)
## 文件输入输出
---
1. 打开文件夹
2. 打开文件
3. 保存文件
4. 标注文件夹指定（可与打开文件夹配合使用，使已标注好的数据显示到界面上）
5. 文件切换
6. **ps**: ***采用voc数据格式*** 
## 图像显示
---
1. 适合窗口显示
2. 放大
3. 缩小
## 图像标注
---
1. 矩形框
2. 标注框选定
3. 标注框删除
4. 标注框移动
5. 标注框修改
6. 标注框已有数据显示（参考1.5）
## 缺陷检测
---
1. 静态图像检测
2. 视频流图像检测

# Software Requirements
1. opencv cpp 4.2.0
2. visual studio 2017
3. QT 5.x
# Training Module Requirements
1. Tensorflow Object Detection V1.13.1
2. tensorflow-gpu 1.13.1
3. *.ckpt->*.pb


