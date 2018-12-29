// Copyright (c) 2017 The Zcash developers
// Copyright (c) 2018-2019 Commercium Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "amqpabstractnotifier.h"
#include "util.h"


AMQPAbstractNotifier::~AMQPAbstractNotifier()
{
}

bool AMQPAbstractNotifier::NotifyBlock(const CBlockIndex * /*CBlockIndex*/)
{
    return true;
}

bool AMQPAbstractNotifier::NotifyTransaction(const CTransaction &/*transaction*/)
{
    return true;
}
