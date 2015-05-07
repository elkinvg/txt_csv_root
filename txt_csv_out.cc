#include "txt_csv_out.h"
void makeCsvFileFromHist(TH1 ** hist,const int numOfHist, int typeOfOut, string suffix)
{

    if (typeid(*hist[0])==typeid(TH1D))
    {
        TH1D *newHist[numOfHist];
        for (int i=0;i<numOfHist;i++)
        {
            newHist[i] = dynamic_cast<TH1D*>(hist[i]);
        }
        makeCsvFileFromHistTemp<TH1D>(newHist,numOfHist, typeOfOut);
    }
    else if (typeid(*hist[0])==typeid(TH1F))
    {
        TH1F *newHist[numOfHist];
        for (int i=0;i<numOfHist;i++)
        {
            newHist[i] = dynamic_cast<TH1F*>(hist[i]);
        }
        makeCsvFileFromHistTemp<TH1F>(newHist, numOfHist,typeOfOut);
    }
}

template <typename T> void makeCsvFileFromHistTemp(T** hist, const int numOfHist, int typeOfOut, string suffix)
{
    string ext;
    string gap;
    switch (typeOfOut) {
    case CSV:
        ext = ".csv";
        gap = ";";
        break;
    case TXT:
        ext = ".txt";
        gap = "\t";
    default:
        ext = ".txt";
        gap = "\t";
        break;
    }

    string filename = "hist" + suffix + ext;
    string filenameRus = "hist_rus" + suffix + ext;

    fstream fileHist(filename.c_str(),ios::out);
    if (!fileHist.is_open()) return;

    fstream fileHistRus(filenameRus.c_str(),ios::out);
    if (!fileHistRus.is_open())
    {
        fileHist.close();
        return;
    }

    for (int i=0;i<hist[0]->GetSize()-1;i++)
    {
        for (int j=0; j<numOfHist;j++)
        {
            if (i==0)
            {
                fileHist << "bin" << gap << "center" << gap << "content" << gap << "xerror" << gap << "binerror";
                fileHistRus << "bin" << gap << "center" << gap << "content" << gap << "xerror" << gap << "binerror";
            }
            else
            {
                fileHist << i << gap << hist[j]->GetBinCenter(i) << gap << hist[j]->GetBinContent(i) << gap  << 0. << gap << hist[j]->GetBinError(i);
                fileHistRus << i << gap << replacePoint((double)hist[j]->GetBinCenter(i)) << gap  << replacePoint((double)hist[j]->GetBinContent(i)) << gap  << "0" << gap << replacePoint((double)hist[j]->GetBinError(i));
            }

            if (j<numOfHist-1)
            {
                fileHist << gap << gap;
                fileHistRus << gap << gap;
            }
            if (j==numOfHist-1 && i<hist[0]->GetSize()-2)
            {
                fileHist << endl;
                fileHistRus << endl;
            }
        }
    }


    fileHist.close();
    fileHistRus.close();
}

string replacePoint(double data)
{
    std::ostringstream ost;
    ost << data;
    string outString = ost.str();

    string::size_type position = outString.find_first_of(".");
    string newstring;
    if (position!=string::npos)
    {
        //newstring = outString.replace(position,1,1,',');
        newstring = outString.replace(position,1,",");
    }
    else newstring = outString;

    return newstring;
}