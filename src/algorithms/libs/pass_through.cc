/*!
 * \file pass_through.cc
 * \brief Brief description of the file here
 * \author Carlos Aviles, 2010. carlos.avilesr(at)googlemail.com
 *
 * Detailed description of the file here if needed.
 *
 * -------------------------------------------------------------------------
 *
 * Copyright (C) 2010-2011  (see AUTHORS file for a list of contributors)
 *
 * GNSS-SDR is a software defined Global Navigation
 *          Satellite Systems receiver
 *
 * This file is part of GNSS-SDR.
 *
 * GNSS-SDR is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * at your option) any later version.
 *
 * GNSS-SDR is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNSS-SDR. If not, see <http://www.gnu.org/licenses/>.
 *
 * -------------------------------------------------------------------------
 */



#include "pass_through.h"

#include <iostream>

#include <gnuradio/gr_io_signature.h>

#include <glog/log_severity.h>
#include <glog/logging.h>

#include "configuration_interface.h"

using google::LogMessage;

PassThrough::PassThrough(ConfigurationInterface* configuration,	std::string role,
        unsigned int in_streams,
        unsigned int out_streams) :
        role_(role),
        in_streams_(in_streams),
        out_streams_(out_streams)
{

    std::string default_item_type = "short";

    item_type_ = configuration->property(role + ".item_type", default_item_type);
    vector_size_ = configuration->property(role + ".vector_size", 1);

    if(item_type_.compare("float") == 0)
        {
            item_size_ = sizeof(float);
        }
    else if(item_type_.compare("gr_complex") == 0)
        {
            item_size_ = sizeof(gr_complex);
        }
    else if(item_type_.compare("short") == 0)
        {
            item_size_ = sizeof(short);
        }
    else
        {
            LOG_AT_LEVEL(WARNING) << item_type_ << " unrecognized item type. Using float";
            item_size_ = sizeof(float);
        }

    kludge_copy_ = gr_make_kludge_copy(item_size_);
    DLOG(INFO) << "kludge_copy(" << kludge_copy_->unique_id() << ")";
}

PassThrough::~PassThrough()
{}

void PassThrough::connect(gr_top_block_sptr top_block)
{
    DLOG(INFO) << "nothing to connect internally";
}

void PassThrough::disconnect(gr_top_block_sptr top_block)
{
    // Nothing to disconnect
}

gr_basic_block_sptr PassThrough::get_left_block()
{
    return kludge_copy_;
}

gr_basic_block_sptr PassThrough::get_right_block()
{
    return kludge_copy_;
}