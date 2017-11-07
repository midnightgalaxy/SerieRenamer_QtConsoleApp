#include <QCoreApplication>
#include <QDir>
#include <QDirIterator>
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::cout << "Hello! This is a little tool for cleaning up serie naming for a season.\n";
    std::cout << "You work it \"season by season\". Make sure there are no trash " <<
                 "files beacause all files are being renamed!\n" <<
                 "Make sure the episoses at least comes in the right order as this "
                 "program iterates over them on by one"
                 "\nfrom first to last!\n";
    std::cout << "-------------------------------------------------------------------------------------------------------------\n";

    std::string path;
    std::string name;
    std::string season = "S";
    std::string extra;
    std::string fileType;

    std::cout << "Enter path (like \"C:\\Users\\Johan\\Desktop\\Dexter\\Season 1\"): ";
    std::cin >> path;
    std::cout << "Enter name of the serie: ";
    std::cin >> name;
    std::cout << "Enter which season (like 05 or 13 etc): ";
    std::string tmp;
    std::cin >> tmp;
    season += tmp;
    std::cout << "Enter extra information (in dot notation, for example: \"720p.BluRay.x264.ShAaNiG\": ";
    std:: cin >> extra;
    std::cout << "Enter what filetype (the suffix only with NO dot, for example avi, mkv, mp4 etc): ";
    std:: cin >> fileType;

    std::cout << "The episodes are gonna be renamed like: " << name << "." << season << "Exx" << "."
              << extra << "." << fileType << "\n";

    std::cout << "Confirm (y or n (n exists application)): ";
    char input;
    std::cin >> input;
    while (input != 'y' && input != 'n')
    {
        std::cout << "Invalid answer!\n";
        std::cout << "Confirm (y or n (n exists application)): ";
        input;
        std::cin >> input;
    }
    if (input == 'n')       // exists application
        return 0;

    else {  // if y then execute operation...

        QDir workPath(path.c_str());

        if (workPath.exists()) {
            int episodeCount = 1;
            QDirIterator it(workPath, QDirIterator::Subdirectories);
            while (it.hasNext())
            {
                QFileInfo tmp(it.next());
                //qDebug() << tmp.fileName() << "is file: " << tmp.isFile() << " ";
                //qDebug() << "absolut file path: " << tmp.absoluteFilePath() << "\n";
                if (tmp.isFile()) {
                    QFile tmp2 (tmp.absoluteFilePath());

                    /*
                    std::string fileRename;
                    fileRename += name;
                    fileRename += ".";
                    fileRename += season;
                    fileRename += "E";
                    if (episodeCount <= 9)
                        fileRename += "0";
                    fileRename += std::to_string(episodeCount);
                    fileRename += ".";
                    fileRename += extra;
                    fileRename += ".";
                    fileRename += fileType;
                    */


                    QString fileRename;
                    fileRename.append(tmp.absolutePath());
                    fileRename.append("/");

                    fileRename.append(name.c_str());
                    fileRename.append(".");
                    fileRename.append(season.c_str());
                    fileRename.append("E");
                    if (episodeCount <= 9)
                        fileRename.append("0");
                    fileRename.append(std::to_string(episodeCount).c_str());
                    fileRename.append(".");
                    fileRename.append(extra.c_str());
                    fileRename.append(".");
                    fileRename.append(fileType.c_str());



                    /*
                    std::string absolutPathfileRename;
                    //absolutPathfileRename = tmp.absoluteFilePath().toStdString();     // full with file name
                    absolutPathfileRename = tmp.absolutePath().toStdString();           // only dir
                    //absolutPathfileRename += "\\";
                    //absolutPathfileRename += fileRename;
                    */

                    qDebug() << "Renamed: "; //<< tmp.absoluteFilePath(); << "\n";      // VARFÖR FUNKAR INTE DETTA!? ANNARS FUNKAR ALLT!!! STÄDA KODEN
                    tmp2.rename(fileRename);   // TODO: PROBLEMET ÄR ATT JAG MÅSTE HA MED HELA ADRESSEN TILL FILEN....



                    episodeCount++;
                }
            }
        }

        std::cout << "\nDone!";
    }

    return a.exec();
}
