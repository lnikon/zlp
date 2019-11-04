#ifndef SOURCETEXTEDIT_H
#define SOURCETEXTEDIT_H

#include <QWidget>
#include <QStatusBar>

#include <optional>

namespace Ui {
class sourceTextEdit;
}

enum class SourceTextEditReturnCode
{
    FILE_LOADED = 0,
    EMPTY_FILENAME
};

class SourceTextEdit : public QWidget
{
    Q_OBJECT

public:
    explicit SourceTextEdit(QWidget *parent = nullptr);
    ~SourceTextEdit();

    std::optional<QString> loadFile();
    void clear();
    void reload();
    void save();

    QString fileName() const;

private:
    Ui::sourceTextEdit* ui;
    QStatusBar*         statusBar_{Q_NULLPTR};
    QString             fileName_{};

    void loadFile(const QString& fileName);
};

#endif // SOURCETEXTEDIT_H
