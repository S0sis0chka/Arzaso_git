#include <QString>
#include <QDebug>

long long gen(long long n){
    n /= 12;
    n *= 13;
    return n;
}

QString encode(QString s, long long n){
    QString num = QString::number(n);
    QString encode_s="";
    for(int i = 0; i < s.size(); i++){
        encode_s.append(QChar((int)s[i].unicode() ^ (int)num[i % num.size()].unicode()));
    }
    return encode_s;
}
