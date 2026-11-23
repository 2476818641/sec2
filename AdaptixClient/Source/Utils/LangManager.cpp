#include <Utils/LangManager.h>
#include <QCoreApplication>
#include <utility>

LangManager& LangManager::instance()
{
    static LangManager inst;
    return inst;
}

LangManager::LangManager(QObject *parent)
    : QObject(parent), m_current("en_US")
{}

QString LangManager::currentLanguage() const
{
    return m_current;
}

bool LangManager::switchLanguage(const QString &langCode)
{
    if (m_current == langCode)
        return true;

    if (langCode != "en_US" && langCode != "zh_CN")
        return false;

    std::unique_ptr<QTranslator> translator;
    if (langCode == "zh_CN") {
        translator = std::make_unique<QTranslator>();
        if (!translator->load(":/translations/adaptix_zh_CN.qm")
            || !QCoreApplication::installTranslator(translator.get()))
            return false;
    }

    if (m_translator)
        QCoreApplication::removeTranslator(m_translator.get());
    m_translator = std::move(translator);
    m_current = langCode;

    Q_EMIT languageChanged();
    return true;
}
