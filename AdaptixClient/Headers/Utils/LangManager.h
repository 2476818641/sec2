#ifndef LANGMANAGER_H
#define LANGMANAGER_H

#include <QObject>
#include <QTranslator>
#include <memory>

class LangManager : public QObject
{
    Q_OBJECT

public:
    static LangManager& instance();

    // "zh_CN" or "en_US"
    QString currentLanguage() const;
    bool    switchLanguage(const QString &langCode);

Q_SIGNALS:
    void languageChanged();

private:
    explicit LangManager(QObject *parent = nullptr);

    std::unique_ptr<QTranslator> m_translator;
    QString                      m_current;
};

#endif // LANGMANAGER_H
