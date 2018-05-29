/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once
#include <eosio/chain/contract_table_objects.hpp>
#include <eosio/chain/controller.hpp>
#include <fc/utility.hpp>
#include <sstream>
#include <algorithm>
#include <set>

namespace chainbase { class database; }

namespace eosio { namespace chain {

class controller;

class memory_db {
   /// Constructor
   public:
      memory_db(controller& con)
      :db(con.db())
      {
      }
   /// Database methods:
   public:
      int  db_store_i64( uint64_t code, uint64_t scope, uint64_t table, const account_name& payer, uint64_t id, const char* buffer, size_t buffer_size );

   private:

      const table_id_object* find_table( name code, name scope, name table );
      const table_id_object& find_or_create_table( name code, name scope, name table, const account_name &payer );
      void                   remove_table( const table_id_object& tid );

   /// Fields:
   public:
      chainbase::database&          db;  ///< database where state is stored
      struct account_info {
         account_name     name;
         asset            available;

         uint64_t primary_key()const { return name; }
      };

      struct bp_info {
         account_name     name;
         public_key_type  producer_key;
         uint32_t         commission_rate;
         asset            total_staked;
         asset            rewards_pool;
         int64_t          total_voteage;
         time_point_sec   voteage_update_time;
         time_point_sec   expiration;
         bool             is_bios;

         uint64_t primary_key() const { return name; }
      };
};
} } // namespace eosio::chain

FC_REFLECT(eosio::chain::memory_db::account_info, (name)(available))
FC_REFLECT(eosio::chain::memory_db::bp_info, (name)(producer_key)
  (commission_rate)(total_staked)(rewards_pool)(total_voteage)(voteage_update_time)(expiration)(is_bios))
