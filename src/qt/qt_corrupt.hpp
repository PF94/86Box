/*
 * Corruptor for 86box
 *
 * By Chaziz/Gamerappa
 */
#ifndef QT_CORRUPT_h
#define QT_CORRUPT_h

#include <QWidget>

class QSlider;
class QSpinBox;
class QLabel;

struct CorruptionControl
{
    const char *label;
    void (*setter)(double);
};

class CorruptionWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CorruptionWindow(QWidget *parent = nullptr);

signals:
    void corruptionChanged(double probability);

private slots:
    void handleValueChanged(int value);

private:
    QSlider *m_slider;
    QSpinBox *m_spinBox;
    QLabel  *m_label;
};

#endif // QT_CORRUPT_h
