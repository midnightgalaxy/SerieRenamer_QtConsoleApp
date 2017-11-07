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
    if (input == 'n') { // exists application
        return 0;
    }
    else {  // if y then execute operation...

        QDir workPath(path.c_str());

        if (workPath.exists()) {
            int episodeCount = 1;
            QDirIterator it(workPath, QDirIterator::Subdirectories);
            while (it.hasNext())
            {
                QFileInfo tmp(it.next());

                if (tmp.isFile()) {
                    QFile tmp2 (tmp.absoluteFilePath());

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

                    std::cout << "Renamed: " << tmp.absoluteFilePath().toStdString() << "\n";
                    tmp2.rename(fileRename);

                    episodeCount++;
                }
            }
            std::cout << "\nDone!";
        } else {
            std::cout << "\nWorkpath didn't existed!";
        }
    }
    return a.exec();
}
