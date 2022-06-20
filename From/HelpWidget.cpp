#include "../Header/HelpWidget.h"

HWheel::HWheel(): QWidget() {
    //本质就是在窗口上绘制一个色轮（包含HSV颜色空间中所有色相）
    // 监测点击事件  然后如果点击事件在窗口里面就响应取色工作
    // 并弹出颜色调节窗口
    svWheel=new SVWheel();
    setStyleSheet("QWidget{background:#000;}");
    //全屏拾色激发按钮
    fullScreenColorPickButton=new
            QPushButton(this);

    QPixmap pixmap = QPixmap("Resource/colorPicker.png");
    fullScreenColorPickButton->setIcon(pixmap);
    //透明背景
    fullScreenColorPickButton->setStyleSheet(
            "QPushButton{border:none;background:transparent;}"
            "QPushButton:hover{background:black;}");

    picker=new ColorPicker(this);
    connect(fullScreenColorPickButton,&QPushButton::clicked,picker,&ColorPicker::pick);
}

void HWheel::resizeEvent(QResizeEvent *event) {
    //每次大小改变时 都保持按钮的位置和图标大小正常
    fullScreenColorPickButton->resize(width()/8,width()/8);
    fullScreenColorPickButton->move(width()-fullScreenColorPickButton->width(),0);
    fullScreenColorPickButton->setIconSize(QSize(width()/8,width()/8 ));
}

void HWheel::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);

    const int r = width()/2;
    resize(width(),width());

    painter.setPen(Qt::NoPen);

    QConicalGradient conicalGradient(0,0,0);
    QColor color;
    //这些绘图算法自己看吧
    color.setHsv(0,255,255);
    conicalGradient.setColorAt(0.0,color);
    color.setHsv(60,255,255);
    conicalGradient.setColorAt(1.0/6,color);
    color.setHsv(120,255,255);
    conicalGradient.setColorAt(2.0/6,color);
    color.setHsv(180,255,255);
    conicalGradient.setColorAt(3.0/6,color);
    color.setHsv(240,255,255);
    conicalGradient.setColorAt(4.0/6,color);
    color.setHsv(300,255,255);
    conicalGradient.setColorAt(5.0/6,color);
    color.setHsv(360,255,255);
    conicalGradient.setColorAt(6.0/6,color);

    painter.translate(r,r);

    painter.setBrush(QBrush(conicalGradient));

    painter.drawEllipse(QPoint(0,0),r,r);
    //画中间的小圆 形成圆环
    painter.setBrush(QBrush(QColor(50,50,50)));
    painter.drawEllipse(QPoint(0,0),r/2,r/2);

}

void HWheel::mousePressEvent(QMouseEvent *event)
{
    const int r = width()/2;
    int distance = sqrt(pow(event->x()-r,2)
            +pow(event->y()-r,2));
    //计算鼠标点击位置到圆心的距离
    //如果小于圆的半径 并大于圆半径的二分之一（中间的小圆） 则进行取色操作
    if(distance<r&&distance>r/2)
    {
        HDC dc = GetDC(0);
        int BGR = GetPixel(dc,event->globalX(),event->globalY());
        int red = BGR & 255;
        int green = BGR >> 8 & 255;
        int blue = BGR >> 16 & 255;
        //获取鼠标所在点颜色
        qDebug()<<QColor(red,green,blue).name();
        svWheel->svShow(event->globalPos(),QColor(red,green,blue));
    }

}

SVWheel::SVWheel() {
    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    //不在任务栏显示  无标题栏  无阴影

    //下面这些看结构应该就能明白吧
    vLayout=new QVBoxLayout();
    vLayout->setMargin(30);
        colorShow=new QLabel();
        vLayout->addWidget(colorShow);

        sValLayout=new QHBoxLayout();
            sValText=new QLabel("H(饱和度):");
            sValLayout->addWidget(sValText);

            sSpinBox=new QSpinBox;
            sSpinBox->setMaximum(255);
            connect(sSpinBox,qOverload<int>(&QSpinBox::valueChanged),
                this,&SVWheel::setS);
            sValLayout->addWidget(sSpinBox);

        vLayout->addLayout(sValLayout);

        vValLayout=new QHBoxLayout();
            vValText=new QLabel("V(明度):");
            vValLayout->addWidget(vValText);

            vSpinBox=new QSpinBox;
            vSpinBox->setMaximum(255);
            connect(vSpinBox,
                    qOverload<int>(&QSpinBox::valueChanged),
                        this,&SVWheel::setV);
            vValLayout->addWidget(vSpinBox);
        vLayout->addLayout(vValLayout);

        rgbLayout=new QHBoxLayout();
            rgbText=new QLabel("RBG");
            rgbLayout->addWidget(rgbText);
            rgbVal=new QLineEdit();
            rgbVal->setReadOnly(true);
            rgbLayout->addWidget(rgbVal);
        vLayout->addLayout(rgbLayout);

        htmlLayout=new QHBoxLayout();
            htmlText=new QLabel("Html");
            htmlLayout->addWidget(htmlText);
            htmlVal=new QLineEdit();
            htmlVal->setReadOnly(true);
            htmlLayout->addWidget(htmlVal);
        vLayout->addLayout(htmlLayout);

    setLayout(vLayout);
}

void SVWheel::svShow(QPoint pos,QColor color) {
    setStyleSheet("QWidget{background:rgb(50,50,50);color:white;}");
    selfColor=color;
    int h,s,v;
    color.getHsv(&h,&s,&v);
    vSpinBox->setValue(v);
    sSpinBox->setValue(s);

    colorShow->setStyleSheet("QLabel{background:"+color.name()+";}");
    colorShow->update();

    rgbVal->setText(QString::number(color.red())+","+
    QString::number(color.green())+","+
    QString::number(color.blue()));

    htmlVal->setText(color.name());
    //设置好一些参数后 将窗口移动到鼠标所在位置并弹出窗口
    move(pos);
    show();
}

void SVWheel::paintEvent(QPaintEvent *event) {
    //为了实现圆角窗口
    QBitmap bmp(this->size());

    bmp.fill();
    QPainter p(&bmp);
    p.setRenderHint(QPainter::Antialiasing,true);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.drawRoundedRect(bmp.rect(),50,50);
    setMask(bmp);
}

ColorPicker::ColorPicker(QWidget* p): QWidget() {
    wid=p;
    setWindowFlag(Qt::FramelessWindowHint);
    photo.load("Resource/colorPicker.png");
}

void ColorPicker::pick() {
    photo=QGuiApplication::primaryScreen()->grabWindow(0);
    //获取整个屏幕的截图

    update();
    showMaximized();
    //最大化
    setCursor(Qt::CrossCursor);
}

void ColorPicker::mousePressEvent(QMouseEvent *event) {
    if(event->button()==Qt::LeftButton)
    {
        //左键
        QColor color=photo.toImage().pixelColor(event->globalPos());
        //获取鼠标所在点颜色
        ((HWheel*)wid)->svWheel->svShow(
                QPoint(wid->x()+wid->width()/2,
                       wid->y()+wid->width()/2),color);
        close();

    }
    else
    {
        //右键
        close();
    }
}

void ColorPicker::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, photo);
}
