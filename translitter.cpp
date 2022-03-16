#include "translitter.h"
#include <QDebug>

QString Translitter::toTranslit(QString line)
{
    QString translit_line, letter;

    for(int i=0; i < line.size(); i++)
    {
        if(russian_upper.filter(line[i]).size() != 0 || russian_lower.filter(line[i]).size() != 0){
            if(line[i].isLower() && line[i].isLetter())
            {
                letter = translit_lower[russian_lower.indexOf(line[i])];
            } else if(line[i].isUpper() && line[i].isLetter())
            {
                letter = translit_upper[russian_upper.indexOf(line[i])];
            }
        } else{
            letter = line[i];
        }
        translit_line.append(letter);
    }
    return translit_line;
}

QString Translitter::fromTranslit(QString line)
{
    QString detranslit_line, letter;
    int index=line.size() - 1;
    while(index >= 0){
        if((line[index].isUpper() || !line[index].isLetter()) && (index == 0 || line[index - 1] != '"'))
        {
            if(line[index].isUpper()) {letter = russian_upper[translit_upper.indexOf(line[index])];}
            else if(translit_lower.indexOf(line[index]) != -1) {letter = russian_lower[translit_lower.indexOf(line[index])];}
            else {letter = line[index];}
            detranslit_line = letter + detranslit_line;
        } else if(line[index] != 'h' && (index == 0 || spec_symbols.filter(line[index - 1]).size() == 0))
        {
            letter = russian_lower[translit_lower.indexOf(line[index])];
            detranslit_line = letter + detranslit_line;
        } else
        {
            letter = QString(line[index - 1]) + QString(line[index]);
            index -= 2;
            while(translit_lower.indexOf(letter) == -1 && translit_upper.indexOf(letter) == -1)
            {
                letter = line[index] + letter;
                index--;
            }
            if(letter[0].isUpper() || letter[1].isUpper()) {letter = russian_upper[translit_upper.indexOf(letter)];}
            else {letter = russian_lower[translit_lower.indexOf(letter)];}
            detranslit_line = letter + detranslit_line;
            index++;
        }
        index--;
    }
    return detranslit_line;
}
