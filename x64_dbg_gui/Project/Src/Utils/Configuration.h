#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QFile>
#include <QString>
#include <QColor>
#include <QMap>
#include <QObject>
#include <QKeySequence>
#include "Bridge.h"

#define Config() (Configuration::instance())
#define ConfigColor(x) (Config()->getColor(x))
#define ConfigBool(x,y) (Config()->getBool(x,y))
#define ConfigUint(x,y) (Config()->getUint(x,y))
#define ConfigFont(x) (Config()->getFont(x))
#define ConfigShortcut(x) (Config()->getShortcut(x).Hotkey)

class Configuration : public QObject
{
    Q_OBJECT
public:
    //Structures
    struct Shortcut
    {
        QString Name;
        QKeySequence Hotkey;
        bool GlobalShortcut;

        Shortcut(QString n = QString(), QString h = QString(), bool g = false)
        {
            Name = n;
            Hotkey = QKeySequence(h);
            GlobalShortcut = g;
        }
    };

    //Functions
    Configuration();
    static Configuration* instance();
    void load();
    void save();
    void readColors();
    void writeColors();
    void readBools();
    void writeBools();
    void readUints();
    void writeUints();
    void readFonts();
    void writeFonts();
    void readShortcuts();
    void writeShortcuts();

    const QColor getColor(const QString id) const;
    const bool getBool(const QString category, const QString id) const;
    void setBool(const QString category, const QString id, const bool b);
    const uint_t getUint(const QString category, const QString id) const;
    void setUint(const QString category, const QString id, const uint_t i);
    const QFont getFont(const QString id) const;
    const Shortcut getShortcut(const QString key_id) const;
    void setShortcut(const QString key_id, const QKeySequence key_sequence);

    //default setting maps
    QMap<QString, QColor> defaultColors;
    QMap<QString, QMap<QString, bool>> defaultBools;
    QMap<QString, QMap<QString, uint_t>> defaultUints;
    QMap<QString, QFont> defaultFonts;
    QMap<QString, Shortcut> defaultShortcuts;

    //public variables
    QMap<QString, QColor> Colors;
    QMap<QString, QMap<QString, bool>> Bools;
    QMap<QString, QMap<QString, uint_t>> Uints;
    QMap<QString, QFont> Fonts;
    QMap<QString, Shortcut> Shortcuts;

    static Configuration* mPtr;

signals:
    void colorsUpdated();
    void fontsUpdated();
    void shortcutsUpdated();

private:
    QColor colorFromConfig(const QString id);
    bool colorToConfig(const QString id, const QColor color);
    bool boolFromConfig(const QString category, const QString id);
    bool boolToConfig(const QString category, const QString id, bool bBool);
    uint_t uintFromConfig(const QString category, const QString id);
    bool uintToConfig(const QString category, const QString id, uint_t i);
    QFont fontFromConfig(const QString id);
    bool fontToConfig(const QString id, const QFont font);
    QString shortcutFromConfig(const QString id);
    bool shortcutToConfig(const QString id, const QKeySequence shortcut);
};

#endif // CONFIGURATION_H
