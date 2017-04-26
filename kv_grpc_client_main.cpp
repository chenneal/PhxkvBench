/*
Tencent is pleased to support the open source community by making 
PhxPaxos available.
Copyright (C) 2016 THL A29 Limited, a Tencent company. 
All rights reserved.

Licensed under the BSD 3-Clause License (the "License"); you may 
not use this file except in compliance with the License. You may 
obtain a copy of the License at

https://opensource.org/licenses/BSD-3-Clause

Unless required by applicable law or agreed to in writing, software 
distributed under the License is distributed on an "AS IS" basis, 
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or 
implied. See the License for the specific language governing 
permissions and limitations under the License.

See the AUTHORS file for names of contributors. 
*/

#include "kv_grpc_client.h"

using namespace std;
using namespace phxkv;

void Put(PhxKVClient & oPhxKVClient, const string & sKey, const string & sValue)
{
    int ret = oPhxKVClient.Put(sKey, sValue);
    if (ret == 0)
    {
        printf("Put ok, key %s value %s\n", 
                sKey.c_str(), sValue.c_str());
        return ;
    }
    else
    {
        printf("Put fail, ret %d, key %s value %s\n", 
                ret, sKey.c_str(), sValue.c_str());
    }
}

void GetGlobal(PhxKVClient & oPhxKVClient, const string & sKey)
{
    string sReadValue;
    int ret = oPhxKVClient.GetGlobal(sKey, sReadValue);
    if (ret == 0)
    {
        printf("GetGlobal key %s value %s\n", 
                sKey.c_str(), sReadValue.c_str());
        return ;
    }
    else if (ret == 1)
    {
        printf("GetGlobal key %s not exist\n", sKey.c_str());
    }
    else if (ret == 101)
    {
        printf("GetGlobal no master\n");
    }
    else
    {
        printf("GetGlobal fail, ret %d key %s\n", ret, sKey.c_str());
    }
}

void GetLocal(PhxKVClient & oPhxKVClient, const string & sKey)
{
    string sReadValue;
    int ret = oPhxKVClient.GetLocal(sKey, sReadValue);
    if (ret == 0)
    {
        printf("GetLocal key %s value %s\n", 
                sKey.c_str(), sReadValue.c_str());
        return ;
    }
    else if (ret == 1)
    {
        printf("GetLocal key %s not exist\n", sKey.c_str());
    }
    else
    {
        printf("GetLocal fail, ret %d key %s\n", ret, sKey.c_str());
    }
}

void Delete(PhxKVClient & oPhxKVClient, const string & sKey)
{
    int ret = oPhxKVClient.Delete(sKey);
    if (ret == 0)
    {
        printf("Delete key %s\n", 
                sKey.c_str());
        return ;
    }
    else
    {
        printf("Delete fail, ret %d key %s\n", ret, sKey.c_str());
    }
}

void usage(char ** argv)
{
    printf("%s <server address ip:port> <put> <key> <value>\n", argv[0]);
    printf("%s <server address ip:port> <getlocal> <key>\n", argv[0]);
    printf("%s <server address ip:port> <getglobal> <key>\n", argv[0]);
    printf("%s <server address ip:port> <delete> <key>\n", argv[0]);
}

int main(int argc, char ** argv)
{
    if (argc < 4)
    {
        usage(argv);
        return -2;
    }

    string sServerAddress = argv[1];

    PhxKVClient oPhxKVClient(grpc::CreateChannel(
                sServerAddress, grpc::InsecureChannelCredentials()));

    string sFunc = argv[2];
    string sKey = argv[3];

    if (sFunc == "put")
    {
        if (argc < 5)
        {
            usage(argv);
            return -2;
        }

        string sValue = argv[4];
        Put(oPhxKVClient, sKey, sValue);
    }
    else if (sFunc == "getlocal")
    {
        GetLocal(oPhxKVClient, sKey);
    }
    else if (sFunc == "getglobal")
    {
        GetGlobal(oPhxKVClient, sKey);
    }
    else if (sFunc == "delete")
    {
        if (argc < 4)
        {
            usage(argv);
            return -2;
        }

        Delete(oPhxKVClient, sKey);
    }
    else
    {
        usage(argv);
    }

    return 0;
}

