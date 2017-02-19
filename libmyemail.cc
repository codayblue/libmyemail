/*
 * =====================================================================================
 *
 *       Filename:  libmyemail.cc
 *
 *    Description:  This will allow mysql to send emails through the mail command.
 *
 *        Version:  1.0
 *        Created:  02/18/2017 07:54:36 PM
 *       Revision:  
 *       Compiler:  g++
 *
 *         Author:  codayblue, 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <cstdlib> /* Needed for system */
#include <mysql/mysql.h> /* Needed for mysql */
#include <cstring> /* needed for string copy */
#include <string> /* Easier to work with strings */

using namespace std;

extern "C" {
   my_bool sendmail_init(UDF_INIT *initid, UDF_ARGS *args, char *message);
   void sendmail_deinit(UDF_INIT *initid);
   long long sendmail(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error);
}

my_bool sendmail_init(UDF_INIT *initid, UDF_ARGS *args, char *message) {

    if(args->arg_count != 3)
    {
        strcpy(message, "Expected 3 arguments");
        return 1; /* Less or more arguments than expected were passed, send back a error */
    }
    
    if(args->arg_type[0] != STRING_RESULT)
    {
        strcpy(message, "First argument is expecting a string value");
        return 1; /* if the argument is not a string send back an error */
    }

    if(args->arg_type[1] != STRING_RESULT)
    {
        strcpy(message, "Second argument is expecting a string value");
        return 1; /* if the argument is not a string send back an error */
    }

    if(args->arg_type[2] != STRING_RESULT)
    {
        strcpy(message, "Third argument is expecting a string value");
        return 1; /* if the argument is not a string send back an error */
    }

    return 0;
}

void sendmail_deinit(UDF_INIT *initid){
}

long long sendmail(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error) {
   int results = 0;
   string cmd;
   string to(args->args[0]);
   string sub(args->args[1]);
   string msg(args->args[2]);
   
   cmd = "echo '" + msg + "' | mail -s '" + sub + "' " + to;
   
   results = system(cmd.c_str());

   return (long long) results;
}

