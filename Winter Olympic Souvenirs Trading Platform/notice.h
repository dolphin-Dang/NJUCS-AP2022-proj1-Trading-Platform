#ifndef _NOTICE_H_
#define _NOTICE_H_

using namespace std;

void send_notice(string u_id, string id, string receiver);	//谁发的，内容是什么，发给谁，备注

void argue(string n_id);	//可以选择向admin argue或者向买家argue

void rejudge(string n_id);	//用户重新评价

void reject(string n_id);	//用户拒绝重新评价


#endif