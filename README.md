# memeToRGB
表情包RGB化&amp;配合使用的魔棒工具

# 注意

## 一定要二值化

7梯度和8Canny边缘检测会有反色的效果，应配合1二值化b使用，来将反色的效果消除

不要操作1-8中出现的预览图像，它一定是无响应的，但显示的图像肯定是对的

但菜单中的yl预览图像，是需要将焦点放在图像上并按任意键才能退出的

# 推荐

一.	1二值化a

二.	1二值化a，2中值滤波

三.	8Canny边缘检测，1二值化b




# 更新记录

1.3.0 加入了混合选项 可生成按照一定比例与原图混合的gif 使生成的gif更具观赏性

1.2.1 修复了透明通道导致的生成错误的bug 修复了魔棒工具的一些bug

1.2.0 优化了gif的生成算法 加入了魔棒工具 可以利用魔棒工具生成的ncc文件制作gif 详见魔棒工具

1.1.2 加入了yl操作，可在列表界面预览图像

1.1.1 加入了exit操作 可随时退出当前进行的图像处理操作

1.1.0 加入了更多的图像操作 可由用户自由处理图像 可随时返回到某一步

1.0.1 修复路径不能带空格的bug 修复了一个可能会导致命名生成的gif时程序崩溃的bug

1.0.0 正式放出程序
