# SUSUAN算子

角点检测算法概述：

角点检测算法可归纳为3类：

基于灰度图像的角点检测、基于二值图像的角点检测、基于轮廓曲线的角点检测。

基于灰度图像的角点检测又可分为基于梯度、基于 模板和基于模板梯度组合3类方法，其中基于模板的方法主要考虑 像素领域点的灰度变化，即图像亮度的变化，将与邻点 亮度对比足够大的点定义为角点。常见的基于 模板的角点检测算法有Kitchen-Rosenfeld角点检测算法，Harris角点检测算法、KLT角点检测算法及SUSAN角点检测算法。和其他角点检测算法相比，SUSAN角点检测算法具有算法简单、位置准确、抗 噪声能力强等特点。

susan算子原理：
SUSAN ( Small univalue segment assimilating nucleus) 算子是一种基于灰度的特征点获取方法, 适用于图像中边缘和角点的检测, 可以去除图像中的噪声, 它具有简单、有效、抗噪声能力强、计算速度快的特点。


SUSAN 算子的模板与常规卷积算法的正方形模板不同, 它采用一种近似圆形的模板, 用圆形模板在图像上移动, 
模板内部每个图像像素点的灰度值都和模板中心像素的灰度值作比较, 若模板内某个像素的灰度与模板中心像素(核)灰度的差值小于一定值, 则认为该点与核具有相同(或相近)的灰度。由满足这一条件的像素组成的区域称为吸收核同值区(Univalue Segment Assimilating Nucleus, USAN)。


susan算子边缘检测：
当圆形模板完全处在背景或目标中时，USAN 区域面积最大；当模板移向目标边缘时，USAN 区域逐渐变小；当模板中心处于边缘时，USAN 区域很小；当模板中心处于角点时，USAN 区域最小。因此，可以通过计算每 1 个像素的 USAN 值，并与设定的门限值进行比较， 如果该像素的 USAN 值小于门限值，则该点可以认为是 1 个边缘点。这就是 SUSAN 算法思想。


susan算子特点：
与其他边缘和角点检测算子相比，SUSAN 算子有一些独特的地方。
（1）在用SUSAN算子对边缘和角点进行检测时不需要计算微分，这使得SUSAN算子对噪声更加鲁棒。

（2）SUSAN检测算子能提供不依赖于模板尺寸的边缘精度。换句话说，最小USAN区域面积的计算是个相对的概念，与模版尺寸无关，所以SUSAN边缘算子的性能不受模版尺寸影响。

（3）控制参数的选择很简单，且任意性小，容易实现自动化选取。



susan算子基本原理详解：

我们可以先借助如图所示来解释检测的原理，其中图片是白色背景，有一个颜色比较暗淡的矩形(dark area)。用一个园形模板在图像上移动，若模板内的像素灰度与模板中心的像素（被称为核Nucleus）灰度值小于一定的阈值，则认为该点与核Nucleus具有相同的灰度，满足该条件的像素组成的区域就称为USAN（Univalue Segment Assimilating  Nucleus）。在图片上有5个圆形区域。圆形区域表示的是掩码区域。把圆形区域内的每一个位置的像素值与圆心处的像素值相比较，那么圆中的的像素可以分为两类，一类是像素值与圆心处的像素值相近的，另一类是像素值与圆心的处的像素值相差比较大的。

![img](https://img-blog.csdn.net/20130721190255796)

如果将模板中各个像素的灰度都与模板中心的核像素的灰度进行比较，那么就会发现总有一部分模板区域和灰度与核像素的灰度相同或相似，这部分区域可以称为USAN(Univalue Segment Assimilating Nuclues).USAN区域包含很多与图像结构有关的信息。利用这种区域的尺寸、重心、二阶矩的分析，可以得到图像中的角点，边缘等信息。从上图所示，当核像素处在图像中的灰度一致区域时，USAN的面积会达到最大。第e个模板就是属于这种情况。

SUSAN（Smallest Univalue Segment Assimilating Nuclues）进行角点检测时，遵循了常规的思路：使用一个窗口在图像上逐点滑动，在每一个位置上计算出一个角点量，再进行局部极大值抑制，得到最终的角点。我们这里使用的窗口是圆形窗口，最小的窗口是3*3的，本文中使用的是37个像素的圆形窗口，如图：

![img](https://img-blog.csdn.net/20130722212110812)

阈值的分析：
在角点检测中，有两种类型的阈值，一种用来约束角点的数量，另一种用来约束角点的质量。当然，一个阈值不能完全做到只影响质量或数量，只是会有一个侧重点。那么，SUSAN中的两个阈值t和g在角点检测中起到一个什么样的作用呢？很明显，阈值g是角点质量的。尽管也会影响数量，但是相对来说更侧重于影响质量（角点的形状）。例如，g值减小，那么SUSAN会更加侧重于检测到更加“尖锐”的角点。所以，可以更加自己的实际需求来确定阈值g。而阈值t，是角点的数量。当t减小时，会检测到更多的角点。所以，阈值t可以在不影响角点质量的情况下，控制检测到的角点的数量。在大多数情况下，设t为25比较合适，如果图像的对比度比较低，可以修改t值以适应变化。通过上面对a、b、c、d、e等几个圆形模板的USAN值的分析，当模板的中心位于角点处时，USAN的值最小。


SUSAN算子检测角点的步骤：
利用圆形模板遍历图像，计算每点处的USAN值。设置一阈值g，一般取值为1/2(Max(n)， 也即取值为USAN最大值的一半，进行阈值化，得到角点响应。使用非极大值抑制来寻找角点。通过上面的方式得到的角点，存在很大伪角点。为了去除伪角点，SUSAN算子可以由以下方法实现：

1，计算USAN区域的重心，然后计算重心和模板中心的距离，如果距离较小则不是正确的角点；
2，判断USAN区域的重心和模板中心的连线所经过的像素都是否属于USAN区域的像素，如果属于那么这个模板中心的点就是角点。
 综上所述，我们基本知道SUSAN角点检测算法。