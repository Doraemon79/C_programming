#include <fstream>
#include <ctime>
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

#define BOOST_NO_CXX11_SCOPED_ENUMS
#include <boost/filesystem.hpp>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <cstring>
#include <boost/crc.hpp>  // for boost::crc_32_type
#define _USE_64_BIT_TIME_T
//  #include <boost/unicode/utf.hpp>
#include <thread>         // std::thread
#include <mutex>          // std::mutex
#include <chrono>
#include <thread>




using namespace std;
using namespace boost::filesystem;
using namespace std::chrono;
std::mutex mtx;

int files_count;
bool copyDir(
    boost::filesystem::path const & source,
    boost::filesystem::path const & destination
)
{
    namespace fs = boost::filesystem;
    try
    {
        // Check whether the function call is valid
        if(
            !fs::exists(source) ||
            !fs::is_directory(source)
        )
        {
            std::cerr << "Source directory " << source.string()
                      << " does not exist or is not a directory." << '\n'
                      ;
            return false;
        }
        if(fs::exists(destination))
        {
            std::cerr << "Destination directory " << destination.string()
                      << " already exists." << '\n'
                      ;
            return false;
        }
        // Create the destination directory
        if(!fs::create_directory(destination))
        {
            std::cerr << "Unable to create destination directory"
                      << destination.string() << '\n'
                      ;
            return false;
        }
    }
    catch(fs::filesystem_error const & e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
    // Iterate through the source directory
    for(
        fs::directory_iterator file(source);
        file != fs::directory_iterator(); ++file
    )
    {
        try
        {
            fs::path current(file->path());
            if(fs::is_directory(current))
            {
                // Found directory: Recursion
                if(
                    !copyDir(
                        current,
                        destination / current.filename()
                    )
                )
                {
                    return false;
                }
            }
            else
            {
                // Found file: Copy
                fs::copy_file(
                    current,
                    destination / current.filename()
                );
            }
        }
        catch(fs::filesystem_error const & e)
        {
            std:: cerr << e.what() << '\n';
        }
    }
    return true;
}


long double check_clock(long size, clock_t start, clock_t end)
{

    long double diff= static_cast<double>(end - start);
    long double brate=size /diff;
  //  cout<<"CHECK bitrate "<<brate<<endl;
    return brate;
}




	int   Check_Size(path beginning,path destination)  //Check the difference of size.
	 {
	    std::string response;
	    cout<<"file of origin "<<beginning<< " is: "<<file_size(beginning)<< " big. file of destination is: "<<file_size(destination)<<" big. Do you want to overwrite (Y/N)"<<std::endl;
	//    getline(cin, response);
	  //    if ((response[0] != 'Y' && response[0] != 'y'))
	    //  {
	 //     std::cout<<"Program stop! "<<'\n';
	//      return true;
	  //  } else {
		//    return false;
	//	}
	    return 0;
	    }


void Check_stats (clock_t start, clock_t end, int size)
{


    cout<<"NUMBER of Files copied:"<<files_count<<endl;
    cout << "CLOCKS_PER_SEC " << CLOCKS_PER_SEC << "\n";
    cout << "CPU-TIME START " << start << "\n";
    cout << "CPU-TIME END " << end << "\n";
    cout << "CPU-TIME END - START " <<  end - start << "\n";
    cout << "TIME(SEC) " << static_cast<double>(end - start) / CLOCKS_PER_SEC << "\n";

}

int change_Permissions(path file_of_destination, int user, const std::string perms )
{

    wpath path = file_of_destination;


    cout<<"Permissions are:"<<endl;

    if (user ==1)
    {
        for ( std::string::const_iterator it=perms.begin(); it!=perms.end(); ++it)
        {
            if (*it=='r' || *it=='R')
            {
                permissions(path,  remove_perms|  owner_read );
            }
            if (*it=='W' || *it=='W')
            {
                permissions(path,  remove_perms|  owner_write );
            }
            if (*it=='W' || *it=='W')
            {
                permissions(path,  remove_perms|  owner_exe );
            }

        }
    }
    if (user ==2)
    {
        for ( std::string::const_iterator it=perms.begin(); it!=perms.end(); ++it)
        {
            if (*it=='r' || *it=='R')
            {
                permissions(path,  remove_perms|  group_read );
            }
            if (*it=='W' || *it=='W')
            {
                permissions(path,  remove_perms|  group_write );
            }
            if (*it=='W' || *it=='W')
            {
                permissions(path,  remove_perms|  group_exe );
            }
        }
    }


    if (user ==3)
    {
        for ( std::string::const_iterator it=perms.begin(); it!=perms.end(); ++it)
        {
            if (*it=='r' || *it=='R')
            {
                permissions(path,  remove_perms|  others_read );
            }
            if (*it=='w' || *it=='W')
            {
                permissions(path,  remove_perms|  others_write );
            }
            if (*it=='x' || *it=='X')
            {
                permissions(path,  remove_perms|  others_exe );
            }
        }

    }

    return 0;
}



int Menu_change_Permissions( path file_ofdestination)
{


    std::string  response;
    std::string avalue;
    std::string bvalue;
    std::string cvalue;
    cin.clear();
    //cin.ignore();
    cout<<"do you want to modify permissions of destination file?" <<endl;
    getline(cin, response);
    if ((response[0] != 'Y' && response[0] != 'y'))
    {
        return 0;
    }


    cout<<"Would you like to modify Owner's permissions,(Y/N)" <<endl;
    getline(cin, response);
    if (!(response[0] != 'Y' && response[0] != 'y'))
    {
        cout<<"which permission would you like to modify, (R)ead,(W)rite, (E)xecute  ?"<<endl;

        getline(cin, avalue);

        change_Permissions(file_ofdestination, 1, avalue);
    }

    cout<<"Would you like to modify(Group's permissions,(Y/N)" <<endl;
    getline(cin, response);
    if (!(response[0] != 'Y' && response[0] != 'y'))
    {
        cout<<"which permission would you like to modify, R)ead,(W)rite, (E)xecute ?"<<endl;

        getline(cin, bvalue);

        change_Permissions(file_ofdestination, 2, bvalue);
    }

    cout<<"Would you like to modify(Others' permissions, (Y/N)" <<endl;
    getline(cin, response);
    if (!(response[0] != 'Y' && response[0] != 'y'))
    {
        cout<<"which permission would you like to modify,R)ead,(W)rite, (E)xecute  ?"<<endl;

        getline(cin, cvalue);
        change_Permissions(file_ofdestination, 3, cvalue);
    }

    return 0;
}


/*
void   Check_Size(path beginning,path destination)  //Check the difference of size.
 {
    std::string response;
    cout<<"file of origin is: "<<file_size(beginning)<< "big. file of destination is: "<<file_size(destination)<<"big. Do you want to overwrite (Y/N)"<<std::endl;
    getline(cin, response);
      if ((response[0] != 'Y' && response[0] != 'y'))
      {
 //     std::cout<<"Program stop! "<<'\n';
      return true;
    } else {
	    return false;
	}
    }
   */
int Cheksum (path file_to_check,int pos)
{
#ifndef PRIVATE_BUFFER_SIZE
#define PRIVATE_BUFFER_SIZE  1024
#endif
    // Global objects
    std::streamsize const  buffer_size = PRIVATE_BUFFER_SIZE;


    // Main program
    //int main ( ])
    try
    {
        boost::crc_32_type  result;

        std::ifstream  ifs(file_to_check.c_str(), ios::binary);

        if ( ifs )
        {
            do
            {
                char  buffer[ buffer_size ];

                ifs.read( buffer, buffer_size );
                result.process_bytes( buffer, ifs.gcount() );
            }
            while ( ifs );
        }
        else
        {
            std::cerr << "Failed to open file '" << file_to_check.c_str() << "'."<< std::endl;
        }
     if (pos==1){
        std::cout << "Checksum of original file is: "<<std::hex << std::uppercase << result.checksum() <<std::endl;

        return EXIT_SUCCESS;
    } else {
    std::cout << "Checksum of file copied is: "<<std::hex << std::uppercase << result.checksum() <<std::endl;

        return EXIT_SUCCESS;}
        }

    catch ( std::exception &e )
    {
        std::cerr << "Found an exception with '" << e.what() << "'." << std::endl;
        return EXIT_FAILURE;
    }
    catch ( ... )
    {
        std::cerr << "Found an unknown exception." << std::endl;
        return EXIT_FAILURE;
    }

}



/*This is the central part of the program, by using boost path it should accept unicode
Based on the paths it receives as input it copyes one file per time through a buffer
it accepts only one flag of overwrite command.
It checks whether the input exists and it makes distinction whether it is a file or a directory.

The buffer works on the stack. I found that on the contrary of what the manual says, in this operation using either the heap or the stak makes no
significant difference, so I used the stack so the wompiler does not throw even more warnings
 */

int Write_to_destination ( path beginning,  path destination)
{


    size_t size;
    std::string  response;
    int i;
    //Counter count;
    //long limit_response;
    int limit_default=0;

    // char buf[limit_default];
     cout<<"File"<<beginning<<"is going to be transferred"<<endl;
    cout<<"Would you like to limit the speed of copy (Y/N)? . (if N default bandwidth will be 128 B/s)"<<endl;
    getline(cin, response);
    // cin>>response;
    if ((response[0] != 'Y' && response[0] != 'y'))
    {
        limit_default=128;
        cout<<"Default at 128 B/s will be kept"<<endl;
   // cin.ignore();
   // cin.clear();


    }
    else
    {
        cout<<"what's the limit you would like"<<endl;

        // getline(cin, limit_response);
        cin>>limit_default;
        //  cin>>limit_response;
        if (limit_default<64 || limit_default>100000)
        {
            cout<<"Sorry you have to choose a bandwidt between 64 and 10000 B/s"<<endl;
            // int Write_to_destination ( path beginning,  path destination);
            // return 0;
            cout<<"For this file we'll use the default limit"<<endl;
            //      char* buf=new char[limit_default];
            limit_default=128;

        }

    }

    // char* buf=new char[limit_default];
    char buf[limit_default];
 //   cin.ignore();
   // cin.clear();

Cheksum(beginning,1);
   // cout<<"IGNAZIO2 "<<endl;
//    FILE* source = fopen(beginning.c_str(), "r");
//    FILE* dest = fopen(destination.c_str(), "w");

mtx.lock();



    FILE* source = fopen(beginning.c_str(), "r");
    FILE* dest = fopen(destination.c_str(), "w");
   // count.IncrementCounter();

    //      high_resolution_clock::time_point new_start = high_resolution_clock::now();
    high_resolution_clock::time_point new_start = high_resolution_clock::now();
    while ((size = fread(buf, 1, sizeof(buf), source))!=0)
    {

        fwrite(buf, 1, size, dest);
    }

   // std::cout<<"Size is: "<<sizeof(buf)<<std::endl;
    high_resolution_clock::time_point new_end = high_resolution_clock::now();


    duration<double> time_span = duration_cast<duration<double>>(new_end - new_start);
    duration<double>  time_span_in_mill=time_span;

    fclose( source );
    fclose( dest );
    Cheksum(destination,0);

  // cout<<"Checksum of is"<< Cheksum(destination)<<endl;
    mtx.unlock();
    files_count++;

    return 0;
}


int Copy_File_to_Dest ( path beginning,  path destination,  int flag_overwrite)
{
    string  filesource,response;
    clock_t start, end;
    start = clock();
    long size;
    if (flag_overwrite==1)
    {
        cout<<"sorry the e option forbids from overwriting file to"<< destination<<endl;
        return 0;
    }

 cout<<"File"<<beginning<<"is "<< file_size(beginning)<<"  big. "<< "Do you want to continue (Y/N) ?"<<endl;
 getline(cin, response);

    if ((response[0] != 'Y' && response[0] != 'y'))
    {
     cout<<"Interrupting for file "<<beginning<<endl;
    return 0;
    }


    Write_to_destination(beginning, destination );
    Menu_change_Permissions(destination);
    size =size + file_size(beginning);

    end = clock();
    check_clock(size,start, end);
    Check_stats (start, end, size);

    return 0;

}


int  Check_Destination ( path beginning,  path destination,  int flag_overwrite)
{

    std::string response;
    if (!exists(destination))
    {
        cout<<"Sorry the destination does not exist"<<endl;
        return 0;
    }
    if (is_directory(destination.c_str()))
    {

        path new_stem=beginning.filename();
        path new_destination=destination;
        new_destination /=new_stem;

        if (exists(new_destination) )
        {
/*         Check_Size(beginning, new_destination) ;
         if ((response[0] != 'Y' && response[0] != 'y'))
                {
                    //you do not want to overwrite
                    return 0;
                }
*/
            if (flag_overwrite==0)
            {
                cout<<"Do you want to overwrite"<< "(Y/N)"<<endl;
                getline(cin, response);
                if ((response[0] != 'Y' && response[0] != 'y'))
                {
                    //you do not want to overwrite
                    return 0;
                }
                else
                {
                    Copy_File_to_Dest( beginning,   new_destination,   flag_overwrite);
                }
            }
            else
            {
                Copy_File_to_Dest( beginning,   new_destination,   flag_overwrite);
            }
        }
        else
        {
            Copy_File_to_Dest( beginning,   new_destination,   flag_overwrite);
        }
    }
    else
        cout<<destination<<"is not a directory"<<endl;


    return 0;
}

int Find_our_File_and_Copy (path bvalue , path cvalue, int flag_overwrite, path exclu_value, path nvalue, int flag_filter )
{


    path p1=bvalue;
    path q1(cvalue);
    //int Flag= flag_filter;


    try
    {
        if (exists(p1))    // does p actually exist?
        {
            if (is_directory(p1))      // is p a directory?
            {

                typedef std::vector<path> vec;             // store paths,
                vec v;                                // so we can sort them later
                copy(directory_iterator(p1), directory_iterator(), back_inserter(v));
                sort(v.begin(), v.end());             // sort, since directory iteration
                // is not ordered on some file systems
                for (vec::const_iterator it(v.begin()); it != v.end(); ++it)
                {

                    path current=*it;
                    //    cout<<"iterator is: " <<current<<endl;

                    if ((exclu_value!=current.extension()) && (nvalue!=current.filename()))
                    {
                        Check_Destination(*it, q1,  flag_overwrite );
                    }
                }

            }
            if (is_regular_file(bvalue))
            {
                if ((exclu_value!=bvalue.extension()) && (nvalue!=bvalue.filename()))
                {
                    Check_Destination(bvalue, q1,  flag_overwrite );
                }
            }
            else
            {
                if (!is_regular_file(bvalue))
                {
                    cout<<"Sorry"<< bvalue<<"is not a regular file"<<endl;
                }
            }
        }


        else
        {
            std::cout << p1 << " does not exist\n";
        }
    }


    catch (const filesystem_error& ex)
    {
        std::cout << ex.what() << '\n';
    }

    return 0;
}


/*I used getopt to make a menu for options, it still imperfect and it is delicate with incomplete options but it actually look nice*/

int main(int argc, char *argv[])
{
  //int test::count=0;
files_count=0;
    int aflag=0;
    int bflag=0;
    int cflag=0;
    int dflag=0;
    int eflag=0;
    int fflag=0;
    int gflag=0;
    int hflag=0;

    int c,a,b,d,e,f,g,h;
    char *avalue = NULL;
    char *bvalue = NULL;
    char *cvalue = NULL;
    char *dvalue = NULL;
    char *evalue = NULL;
    char *fvalue = NULL;
    char *gvalue = NULL;
    char *hvalue = NULL;


    while ((c = getopt (argc, argv, "a:b:c:d:efg:h:")) != -1)  //options aflag=checksum bflag=bitrate c=size d= recursive in a directory
        //e specific file and f destination path g file name of destination
    {
        switch (c)
        {
        case 'a':                    //file  of origin
            avalue = optarg;
            aflag=1;
            break;
        case 'b':                    //folder  of origin
            bvalue = optarg;
            bflag=1;
            break;
        case 'c':                    //folder or file of destination
            cvalue = optarg;
            cflag=1;
            break;
        case 'd':
            dflag=1;
            break;
        case 'e':                    //1 never overwrite
            //       evalue = optarg;
            eflag=1;
            break;
        case 'f':                       //with or without filters
            //   fvalue = optarg;
            fflag=1;
            break;
        case 'g':                       //exclude files with extension .xxx  exclusion by size is done already by the filter
            gvalue = optarg;
            gflag=1;
            break;
        case 'h':                       //exclude files with extension .xxx  exclusion by size is done already by the filter
            hvalue = optarg;
            hflag=1;
            break;
        case '?':
            if (optopt == 'c')
                fprintf (stderr, "Option -%c requires an argument. Usage: ./SpaceComp -a file of orgin -bfolder of origin -c folder or file of destination -e Overwrite -g ext to exclude -hfile to exclude \n", optopt);
            else if (isprint (optopt))
                fprintf (stderr, "Option -%c requires an argument. Usage: ./SpaceComp -a file of orgin -bfolder of origin -c folder or file of destination -e Overwrite -g ext to exclude -hfile to exclude \n", optopt);

            //  fprintf (stderr, "Unknown option `-%c'.\n", optopt);
            else
                fprintf (stderr,
                         "Unknown option character `\\x%x'.\n",
                         optopt);
            return 1;

        default:

            abort ();
        }
    }
    // printf (" avalue=%s, bflag = %d, cflag = %d, cvalue = %s\n",
    //            bvalue, bflag, cflag, cvalue);
    if(gvalue==NULL)
    {
        gvalue="NUL.NUL";
    }
    if(hvalue==NULL)
    {
        hvalue="NUL.NUL";
    }

    if ((aflag==1) && (cflag==1) ) //copy file without filters
    {
        path p(avalue);
        path q(cvalue);
        Check_Destination(p,q,eflag);
    }

    if ((bflag==1) && (cflag==1) ) //copy directory without filters
    {

        path p(bvalue);

        path q(cvalue);


        path g(gvalue);
        path h(hvalue);

        Find_our_File_and_Copy(p,q,eflag,g,h,fflag);
    }
    return 0;
}
