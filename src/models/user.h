#pragma once
#include <sqlpp11/table.h>
#include <sqlpp11/data_types.h>
#include <sqlpp11/char_sequence.h>

namespace models {
namespace user_table_ {

    struct Id {
        struct _alias_t {
            static constexpr const char _literal[] = "id";
        };
        using _traits = sqlpp::make_traits<sqlpp::integer, sqlpp::tag::can_be_null>;
    };

    struct DiscordId {
        struct _alias_t {
            static constexpr const char _literal[] = "discord_id";
        };
        using _traits = sqlpp::make_traits<sqlpp::text, sqlpp::tag::can_be_null>;
    };

    struct Username {
        struct _alias_t {
            static constexpr const char _literal[] = "username";
        };
        using _traits = sqlpp::make_traits<sqlpp::text, sqlpp::tag::can_be_null>;
    };

    struct Discriminator {
        struct _alias_t {
            static constexpr const char _literal[] = "discriminator";
        };
        using _traits = sqlpp::make_traits<sqlpp::text, sqlpp::tag::can_be_null>;
    };

    struct CreatedAt {
        struct _alias_t {
            static constexpr const char _literal[] = "created_at";
        };
        using _traits = sqlpp::make_traits<sqlpp::text, sqlpp::tag::can_be_null>;
    };

}

struct User : sqlpp::table_t<User,
    user_table_::Id,
    user_table_::DiscordId,
    user_table_::Username,
    user_table_::Discriminator,
    user_table_::CreatedAt> {
    struct _alias_t {
        static constexpr const char _literal[] = "users";
    };
};

}
