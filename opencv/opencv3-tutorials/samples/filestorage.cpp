#include <opencv2/core.hpp>

#include <string>
#include <iostream>

using namespace cv;
using namespace std;

static void help(char **argv)
{
  cout << "\nfilestorage_sample demonstrate the usage of the opencv serialization functionality.\n"
       << "usage:\n"
       <<  argv[0] << " outputfile.yml.gz\n"
       << "\n   outputfile above can have many different extensions, see below."
       << "\nThis program demonstrates the use of FileStorage for serialization, that is in use << and >>  in OpenCV\n"
       << "For example, how to create a class and have it serialize, but also how to use it to read and write matrices.\n"
       << "FileStorage allows you to serialize to various formats specified by the file end type."
       << "\nYou should try using different file extensions.(e.g. yaml yml xml xml.gz yaml.gz etc...)\n" << endl;
}

struct MyData
{
    MyData() : A(0), X(0), id() {}
    explicit MyData(int) : A(97), X(CV_PI), id("mydata1234") {}
    int A;
    double X;
    string id;
    void write(FileStorage &fs) const
    {
        fs << "{" << "A" << A << "X" << X << "id" << id << "}"; 
    }
    void read(const FileNode &node)
    {
        A = (int) node["A"];
        X = (double) node["X"];
        id = (string) node["id"];
    }
};

static void write(FileStorage &fs, const string &, const MyData &x)
{
    x.write(fs);
}

static void read(const FileNode &node, MyData &x, const MyData &default_value = MyData())
{
    if (node.empty())
        x = default_value;
    else
        x.read(node);
}

static ostream& operator<<(ostream &out, const MyData &m)
{
    out << "{ id = " << m.id << ", ";
    out << "X = " << m.X << ", ";
    out << "A = " << m.A << "}";
    return out;
}

int main(int argc, char **argv)
{
    CommandLineParser parser(argc, argv, "{@input||}{help h||}");
    if (parser.has("help")) {
        help(argv);
        return 0;
    }

    string filename = parser.get<string>("@input");
    if (filename.empty()) {
        help(argv);
        return 1;
    }

    // write
    {
        FileStorage fs(filename, FileStorage::WRITE);

        cout << "writing images\n";
        fs << "images" << "[";

        fs << "image1.jpg" << "myfi.png" << "baboon.jpg";
        cout << "image1.jpg" << " myfi.png" << " baboon.jpg" << endl;

        fs << "]";

        cout << "writing mats\n";
        Mat R = Mat_<double>::eye(3, 3), T = Mat_<double>::zeros(3, 1);
        cout << "R =" << R << endl;
        cout << "T =" << T << endl;
        fs << "R" << R;
        fs << "T" << T;

        cout << "writing MyData struct" << endl;
        MyData m(1);
        cout << m << endl;
        fs << "mdata" << m;
    }

    // read
    {
        FileStorage fs(filename, FileStorage::READ);
        if (!fs.isOpened()) {
            cerr << "failed to open " << filename << endl;
            help(argv);
            return 1;
        }

        FileNode n = fs["images"];
        if (n.type() != FileNode::SEQ) {
            cerr << "images is not a sequence! FAIL" << endl;
            return 1;
        }

        cout << "reading images\n";
        FileNodeIterator it = n.begin(), it_end = n.end();
        for ( ; it != it_end; ++it) {
            cout << (string) *it << "\n";
        }

        Mat R, T;
        cout << "reading R and T" << endl;

        fs["R"] >> R;
        fs["T"] >> T;

        cout << "R = " << R << endl;
        cout << "T = " << T << endl;

        MyData m;
        fs["mdata"] >> m;

        cout << "read mdata" << endl;
        cout << m << endl;

        cout << "attempting to read mdata_b" << endl;
        fs["mdata_b"] >> m;
        cout << "read mdata_b" << endl;
        cout << m << endl;
    }

    cout << "Try opening " << filename << " to see the serialized data." << endl << endl;

    // read from string
    {
        cout << "Read data from string\n";
        string dataString =
            "%YAML:1.0\n"
            "mdata:\n"
            "   A: 97\n"
            "   X: 3.1415926535897931e+00\n"
            "   id: mydata1234\n";
        MyData m;
        FileStorage fs(dataString, FileStorage::READ | FileStorage::MEMORY);
        fs["mdata"] >> m;
        cout << "read mdata" << endl;
        cout << m << endl;
    }

    // write to string
    {
        cout << "Write data to string" << endl;
        FileStorage fs(filename, FileStorage::WRITE | FileStorage::MEMORY | FileStorage::FORMAT_YAML);

        cout << "writing MyData struct" << endl;
        MyData m(1);
        fs << "mdata" << m;
        cout << m << endl;
        string createdString = fs.releaseAndGetString();
        cout << "Created string:\n" << createdString << endl;
    }

    return 0;
}
