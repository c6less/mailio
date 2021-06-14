/*
smtps_simple_msg.cpp
--------------------
Connects to SMTP server via START_TLSand sends a simple message.
Copyright(C) 2016, Tomislav Karastojkovic(http://www.alepho.com).
Distributed under the FreeBSD license, see the accompanying file LICENSE or
copy at http ://www.freebsd.org/copyright/freebsd-license.html.
*/


#include <iostream>
#include <string>
#include <mailio/message.hpp>
#include <mailio/smtp.hpp>

using mailio::message;
using mailio::mail_address;
using mailio::smtps;
using mailio::smtp;
using mailio::smtp_error;
using mailio::dialog_error;
using std::cout;
using std::cin;
using std::string;
using std::endl;


void getParams(string& serverName, string& senderEmail, string& senderPassword, string& recipientEmail, bool &enabledSSL, bool &enabledTLS);


int main()
{
    string sender;
    string recipient;
    string password;
    string smtpServer;
    bool enabledSSL;
    bool enabledTLS;


    getParams(smtpServer, sender, password, recipient, enabledSSL, enabledTLS);
    cout << endl << "Outgoing server: " << smtpServer << endl;
    cout << "Sender email: " << sender << endl;
    cout << "Password: " << password << endl;
    cout << "Recipient email: " << recipient << endl;

    // debug.
    //sender = "rachel@wolfcreekmicro.com"; 
    //password = "123Rachel456";
    //recipient = "rachel@wolfcreekmicro.com";
    //smtpServer = "mail.wolfcreekmicro.com";

    try
    {
        
        //// create mail message
        message msg;
        msg.from(mail_address("sender", sender));// set the correct sender name and address
        msg.add_recipient(mail_address("recipient", recipient));// set the correct recipent name and address
        msg.subject("smtp simple message");
        msg.content("Hello, World!");

        if(enabledTLS)
        {
            //// connect to server
            smtps conn(smtpServer, 587);
            conn.authenticate(sender, password, smtps::auth_method_t::START_TLS);
            conn.submit(msg);
        }
        else
        {
            if(enabledSSL)
            {
                //// connect to server
                smtps conn(smtpServer, 587);
                conn.authenticate(sender, password, smtps::auth_method_t::LOGIN);
                conn.submit(msg);
            }
            else
            {
                //// connect to server
                smtp conn(smtpServer, 587);
                conn.authenticate(sender, password, smtp::auth_method_t::LOGIN);
                conn.submit(msg);
            }
        }

    }
    catch(smtp_error &exc)
    {
        cout << exc.what() << endl;
    }
    catch(dialog_error &exc)
    {
        cout << exc.what() << endl;
    }

    return EXIT_SUCCESS;
}

void getParams(string &serverName, string &senderEmail, string &senderPassword, string &recipientEmail, bool &enabledSSL, bool &enabledTLS)
{
    char ssl_enable;
    char tls_enable;

    cout << "Enter outgoing server name:\n";
    cin >> serverName;
    cout << "\nIs TLS enabled? (Y/N):\n";
    cin >> tls_enable;
    cout << "\nIs SSL enabled? (Y/N):\n";
    cin >> ssl_enable;
    cout << "\nEnter sender email:\n";
    cin >> senderEmail;
    cout << "\nEnter sender password:\n";
    cin >> senderPassword;
    cout << "\nEnter recipient email address.\n";
    cin >> recipientEmail;
    cout << endl;
    // set SSL enable    
    if((ssl_enable == 'Y') || (ssl_enable == 'y'))
    {
        enabledSSL = true;
    }
    else
    {
        enabledSSL = false;
    }
    // set TLS enable    
    if ((tls_enable == 'Y') || (tls_enable == 'y'))
    {
        enabledTLS = true;
    }
    else
    {
        enabledTLS = false;
    }
}