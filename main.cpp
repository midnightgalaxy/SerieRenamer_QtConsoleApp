#include <QCoreApplication>
#include <QDir>
#include <QDirIterator>
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::cout << "This is a little tool for cleaning up serie naming for a season.\n";
    std::cout << "You work it \"season by season\". Make sure there are no trash " <<
                 "files beacause all files are being renamed!\n" <<
                 "Make sure the episodes at least comes in the right order as this "
                 "program iterates over them on by one"
                 "\nfrom first to last!\n";
    std::cout << "-------------------------------------------------------------------------------------------------------------\n";

    std::string path;
    std::string name;
    std::string season = "S";
    std::string extra;
    std::string fileType;

    std::cout << "Enter path (like \"C:\\Users\\Johan\\Desktop\\Dexter\\Season_1\", NO blancs!): ";
    std::cin >> path;
    std::cout << "Enter name of the serie (dot notation please): ";
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
    while (input != 'y' && input != 'n') // make sure a correct answer is given
    {
        std::cout << "Invalid answer!\n";
        std::cout << "Confirm (y or n (n exists application)): ";
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

                    QString fileRenamePreview;

                    fileRenamePreview.append(name.c_str());
                    fileRenamePreview.append(".");
                    fileRenamePreview.append(season.c_str());
                    fileRenamePreview.append("E");
                    if (episodeCount <= 9)
                        fileRenamePreview.append("0");
                    fileRenamePreview.append(std::to_string(episodeCount).c_str());
                    fileRenamePreview.append(".");
                    fileRenamePreview.append(extra.c_str());
                    fileRenamePreview.append(".");
                    fileRenamePreview.append(fileType.c_str());

                    fileRename.append((fileRenamePreview));

                    std::cout << "Renamed: " << tmp.absoluteFilePath().toStdString() << " -> " << fileRenamePreview.toStdString() << "\n";
                    tmp2.rename(fileRename);

                    episodeCount++;
                }
            }
            if (episodeCount == 1)
                std::cout << "\nNo files to rename!";
            std::cout << "\nDone!";
        } else {
            std::cout << "\nWorkpath didn't existed!";
        }
    }
    return a.exec();
}
