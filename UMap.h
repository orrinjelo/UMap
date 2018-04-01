/*
 * UMap.h
 *
 *  Created on: July 1, 2017
 *      Author: orrinjelo
 */
 
#pragma once

#include <string>
#include <map>
#include <typeinfo>
#include <exception>
#include <memory>

/*
 *  Usage: 
 *      UMap uMap;
 *      uMap["myString"] = "string";
 *      uMap["myFloat"]  = 2.3f;
 *      uMap["myDouble"] = 2.3;
 *      uMap["myInt"]    = 42;
 */

typedef struct entryStruct UMapEntry;
class UMap
{
    public:
        UMap() {};

        virtual ~UMap() {};

        template <class T>
        T& get( const char* key ) 
        {
            if (uMapMap.find(key) == uMapMap.end()) 
            {
                std::string key_str(key);
                key_str += " is not a valid key.";
                throw std::runtime_error(key_str.c_str());
            }

            auto temp = uMapMap[std::string(key)];
            return *(reinterpret_pointer_cast<T>(temp));
        }

        typedef struct entryStruct
        {
            std::string   key;
            UMap*         uMap;

            template <class T>
            void operator=( const T& value )
            {
                uMap->store(key.c_str(), value);
            }

            template <class T>
            T& as()
            {
                return uMap->get<T>(key.c_str());
            }

            template <class T>
            T as(T defaultValue)
            {
                if (uMap->isKey(key.c_str()))
                    return uMap->get<T>(key.c_str());
                else
                    return defaultValue;
            }
        } UMapEntry;

        inline UMapEntry operator[]( std::string s )
        {
            UMapEntry entry;
            entry.key = s;
            entry.uMap = this;
            return entry;
        }

        inline UMapEntry operator[]( const char* s )
        {
            UMapEntry entry;
            entry.key = std::string(s);
            entry.uMap = this;
            return entry;
        }

        template <class T>
        void store( const char* key, const T& data )
        {
            if (uMapMap.find(std::string(key)) != uMapMap.end())
            {
                uMapMap.erase(std::string(key));
            }
            auto newData = std::make_shared<T>(data);
            uMapMap[std::string(key)] = reinterpret_pointer_cast<char>(newData);
        }

        inline bool isKey( const char* key )
        {
            if (uMapMap.find(std::string(key)) != uMapMap.end())
                return true;
            return false;
        }

        inline bool isKey( std::string key )
        {
            if (uMapMap.find(key) != uMapMap.end())
                return true;
            return false;
        }


    protected:
        std::map< std::string, std::shared_ptr<char> > uMapMap;

    private:
        template< class T, class U > 
        std::shared_ptr<T> reinterpret_pointer_cast( const std::shared_ptr<U>& r ) noexcept
        {
            auto p = reinterpret_cast<typename std::shared_ptr<T>::element_type*>(r.get());
            return std::shared_ptr<T>(r, p);
        }        

};
