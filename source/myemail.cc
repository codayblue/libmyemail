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
 *       Compiler:  g++ or clang
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
#include <sstream> /* use a string stream to split a comma delimited string */
#include "Poco/Net/SecureSMTPClientSession.h" /* Send the email over TLS this is needed */
#include "Poco/Net/SMTPClientSession.h" /* The secure method relies on this and also is used to send over nonsecure */
#include "Poco/Net/MailMessage.h" /* Represents the email being sent */
#include "Poco/Net/NetException.h" /* SMTP and Net exceptions so they can be caught */


using namespace std;
using namespace Poco::Net;

extern "C" {
   my_bool sendmail_init(UDF_INIT *initid, UDF_ARGS *args, char *message);
   void sendmail_deinit(UDF_INIT *initid);
   char *sendmail(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);
}

string send(string host, string user, string pass, long long port, SMTPClientSession::Recipients to, MailMessage &msg, char *error);
string sendSecure(string host, string user, string pass, long long port, SMTPClientSession::Recipients to, MailMessage &msg, char *error);

my_bool sendmail_init(UDF_INIT *initid, UDF_ARGS *args, char *message) {

    if(args->arg_count != 9)
    {
        strcpy(message, "Expected 9 arguments");
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

    if(args->arg_type[3] != STRING_RESULT)
    {
        strcpy(message, "Fourth argument is expecting a string value");
        return 1; /* if the argument is not a string send back an error */
    }

    if(args->arg_type[4] != STRING_RESULT)
    {
        strcpy(message, "Fifth argument is expecting a string value");
        return 1; /* if the argument is not a string send back an error */
    }

    if(args->arg_type[5] != INT_RESULT)
    {
        strcpy(message, "Sixth argument is expecting an Interger value");
        return 1; /* if the argument is not a string send back an error */
    }

    if(args->arg_type[6] != STRING_RESULT)
    {
        strcpy(message, "Seventh argument is expecting a string value");
        return 1; /* if the argument is not a string send back an error */
    }

    if(args->arg_type[7] != STRING_RESULT)
    {
        strcpy(message, "Eighth argument is expecting a string value");
        return 1; /* if the argument is not a string send back an error */
    }

    if(args->arg_type[8] != INT_RESULT)
    {
        strcpy(message, "Ninth argument is expecting an Interger value");
        return 1; /* if the argument is not a string send back an error */
    }

    return 0;
}

void sendmail_deinit(UDF_INIT *initid){
}

char *sendmail(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error) {

    string from(args->args[0]);
    string to(args->args[1]);
    string sub(args->args[2]);
    string msg(args->args[3]);
    string host(args->args[4]);
    string uname(args->args[6]);
    string pass(args->args[7]);
    string results;

    long long port = *((long long*) args->args[5]);
    long long secure = *((long long*) args->args[8]);

    string buff;
    stringstream ss(to);
    SMTPClientSession::Recipients toList;

    MailMessage message;

    /* Brake up the comma list of recipients into the vector */
    while(getline(ss, buff, ','))
    {
        toList.push_back(buff);
    }

    /* Create the message */
    message.setSender(from);
    message.setSubject(sub);
    message.setContent(msg);

    /* Send either via secure or insecure */
    if (secure == 1)
    {
        results = sendSecure(host, uname, pass, port, toList, message, error);
    }
    else
    {
        results = send(host, uname, pass, port, toList, message, error);
    }

    /* Send the results back to mysql */
    if (results.size() >= MYSQL_ERRMSG_SIZE)
    {
        memcpy(result, results.c_str(), MYSQL_ERRMSG_SIZE);
        *length = MYSQL_ERRMSG_SIZE;
    }
    else
    {
        memcpy(result, results.c_str(), results.size());
        *length = results.size();
    }

    return result;
}

string send(string host, string user, string pass, long long port, SMTPClientSession::Recipients to, MailMessage &msg, char *error) {
    SMTPClientSession session(host, port);

    string results = "Message Sent";

    try
    {
        session.login(SMTPClientSession::AUTH_LOGIN, user, pass);

        session.sendMessage(msg, to);
    }
    catch(SMTPException &e)
    {
        *error = 1;
        results = "SMTP Exception: " + e.message();
    }
    catch(NetException &e)
    {
        *error = 1;
        results = "Net Exception: " + e.message();
    }

    session.close();

    return results;
}

string sendSecure(string host, string user, string pass, long long port, SMTPClientSession::Recipients to, MailMessage &msg, char *error) {
    SecureSMTPClientSession session(host, port);

    string results = "Message Sent";

    try
    {
        session.login();
        session.startTLS();
        session.login(SMTPClientSession::AUTH_LOGIN, user, pass);

        session.sendMessage(msg, to);
    }
    catch(SMTPException &e)
    {
        *error = 1;
        results = "SMTP Exception: " + e.message();
    }
    catch(NetException &e)
    {
        *error = 1;
        results = "Net Exception: " + e.message();
    }

    session.close();

    return results;
}
