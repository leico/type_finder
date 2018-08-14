//
//  type_finder.h
//
//
//  Created by leico on 2018/08/14.
//  Copyright © 2018年 leico_studio. All rights reserved.
//

#ifndef type_finder_h
#define type_finder_h

#include <type_traits> 

namespace type_finder {
    
    // when type not found, meta functions returned this type;
    struct not_found {  };
    
    //template for finder meta function
    template <
    template < typename, typename > class Conditioner
    , typename    Target
    , typename... Args
    >
    class finder_template {
        
    public:
        using not_found = not_found;
        
    private:
        
        template <
        template < typename, typename > class Cond
        , typename    InTarget
        , typename... NoArgs
        >
        struct impl {
            using type = not_found;
        };
        
        
        template <
        template < typename, typename > class Cond
        , typename    InTarget
        , typename    Head
        , typename... Tail
        >
        struct impl < Cond, InTarget, Head, Tail... > {
            using type = typename std :: conditional<
            Cond< InTarget, Head > :: value
            , InTarget
            , typename impl< Cond, InTarget, Tail... > :: type
            > :: type;
        };
        
        
    public:
        
        using type = typename impl< Conditioner, Target, Args... > :: type;
        
    };
    
    
    //find same type
    template < typename Target, typename... Args >
    struct same {
        using not_found = not_found;
        using type      = typename finder_template < std :: is_same, Target, Args... > :: type;
    };
    
    //find same or inherited from target
    template < typename Target, typename... Args >
    struct same_base {
        using not_found = not_found;
        using type      = typename finder_template < std :: is_base_of, Target, Args... > :: type;
    };
    
    
    //boolean returned same type finder
    template < typename Target, typename ...Args >
    struct is_same {
        
        using not_found = not_found;
        
        static constexpr bool value = std :: is_same<
        Target
        , typename same < Target, Args... > :: type
        > :: value;
        
        
    };
    
    //boolean returned same or inherited from target finder
    template < typename Target, typename... Args >
    struct is_same_base {
        
        using not_found = not_found;
        
        static constexpr bool value = std :: is_same<
        Target
        , typename same_base < Target, Args... > :: type
        > :: value;
    };
    
    
}

#endif /* type_finder_h */
