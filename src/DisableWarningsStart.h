//Disable as many warnings as I can

#if defined(__clang__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wall"
# pragma clang diagnostic ignored "-Wextra" 
# pragma clang diagnostic ignored "-pedantic""
#endif

//Just push a rediculously low warning here
#if defined(_MSC_VER)
# pragma warning(push, 0)
#endif
