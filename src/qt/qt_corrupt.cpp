/*
 * Corruptor for 86box
 *
 * By Chaziz/Gamerappa
 */
#include "qt_corrupt.hpp"

extern "C" {
#include <86box/corrupt.h>
}

#include <QSlider>
#include <QSpinBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

static CorruptionControl controls[] = {
    { "GPU Input",         corrupt_set_gpu_in },
    { "GPU Output",        corrupt_set_gpu_out },
    { "GPU Render",        corrupt_set_gpu_render },
    { "HDD Read",          corrupt_set_hdd_read },
    { "Keyboard Input",    corrupt_set_kb },
};

CorruptionWindow::CorruptionWindow(QWidget *parent)
    : QWidget(nullptr)
{
    setWindowTitle("Corruptor");
    setMinimumWidth(300);

    // make it unclosable (theres no way to reopen it for now)
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowCloseButtonHint);

    QVBoxLayout *mainLayout = new QVBoxLayout;

    for (const CorruptionControl &ctrl : controls)
    {
        QLabel *label = new QLabel(ctrl.label);

        QSlider *slider = new QSlider(Qt::Horizontal);
        slider->setRange(0, 100);
        slider->setValue(0);

        QSpinBox *spinBox = new QSpinBox;
        spinBox->setRange(0, 100);
        spinBox->setSuffix("%");
        spinBox->setValue(0);

        connect(slider, &QSlider::valueChanged,
                spinBox, &QSpinBox::setValue);

        connect(spinBox, QOverload<int>::of(&QSpinBox::valueChanged),
                slider, &QSlider::setValue);

        connect(slider, &QSlider::valueChanged,
                this,
                [setter = ctrl.setter](int value)
                {
                    double probability = value / 100.0;
                    setter(probability);
                });

        QHBoxLayout *row = new QHBoxLayout;
        row->addWidget(label);
        row->addWidget(slider);
        row->addWidget(spinBox);

        mainLayout->addLayout(row);
    }

    setLayout(mainLayout);
}

void CorruptionWindow::handleValueChanged(int value)
{
    double probability = value / 100.0;
    emit corruptionChanged(probability);
}