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

#pragma once

#include <grpc++/grpc++.h>
#include "phxkv.grpc.pb.h"
#include "kv_paxos.h"

namespace phxkv
{

class PhxKVServiceImpl final : public PhxKVServer::Service 
{
public:
    PhxKVServiceImpl(const phxpaxos::NodeInfo & oMyNode, const phxpaxos::NodeInfoList & vecNodeList,
            const std::string & sKVDBPath, const std::string & sPaxosLogPath, const int & iGroupCount);

    int Init();
    
    grpc::Status Put(grpc::ServerContext* context, const KVOperator * request, KVResponse * reply) override;

    grpc::Status GetLocal(grpc::ServerContext* context, const KVOperator * request, KVResponse * reply) override;

    grpc::Status GetGlobal(grpc::ServerContext* context, const KVOperator * request, KVResponse * reply) override;

    grpc::Status Delete(grpc::ServerContext* context, const KVOperator * request, KVResponse * reply) override;

private:
    PhxKV m_oPhxKV;
};

}
