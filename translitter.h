#ifndef TRANSLITTER_H
#define TRANSLITTER_H
#include <QString>
#include <QStringList>



class Translitter
{
private:
    QStringList spec_symbols={"j", "J", "\""};
    QStringList russian_lower={"а", "б", "в", "г", "д", "е", "ё", "ж", "з", "и", "й", "к", "л", "м", "н", "о", "п", "р", "с", "т", "у", "ф", "х", "ц", "ч", "ш", "щ", "ъ", "ы", "ь", "э", "ю", "я"};
    QStringList translit_lower={"a", "b", "v", "g", "d", "e", "jo", "zh", "z", "i", "y", "k", "l", "m", "n", "o", "p", "r", "s", "t", "u", "f", "kh", "c", "ch", "sh", "s'h", "\"", "y", "'", "\"e", "ju", "ja"};
    QStringList russian_upper={"А", "Б", "В", "Г", "Д", "Е", "Ё", "Ж", "З", "И", "Й", "К", "Л", "М", "Н", "О", "П", "Р", "С", "Т", "У", "Ф", "Х", "Ц", "Ч", "Ш", "Щ", "Ъ", "Ы", "Ь", "Э", "Ю", "Я"};
    QStringList translit_upper={"A", "B", "V", "G", "D", "E", "Jo", "Zh", "Z", "I", "Y", "K", "L", "M", "N", "O", "P", "R", "S", "T", "U", "F", "Kh", "C", "Ch", "Sh", "S'h", "\"", "Y", "'", "\"E", "Ju", "Ja"};
public:
    QString toTranslit(QString line);
    QString fromTranslit(QString line);
};

#endif // TRANSLITTER_H
