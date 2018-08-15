//
//  type_finder.h
//
//  MIT License
//  
//  Copyright (c) 2018 leico
//  
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//  
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//  
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.
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
