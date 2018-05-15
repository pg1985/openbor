/*
 * OpenBOR - http://www.chronocrash.com
 * -----------------------------------------------------------------------
 * All rights reserved. See LICENSE in OpenBOR root for license details.
 *
 * Copyright (c) 2004 OpenBOR Team
 */

// Axis Properties
// 2018-05-13
// Caskey, Damon V.

#include "scriptcommon.h"

// Use string property argument to find an
// integer property constant and populate
// varlist->lval.
int mapstrings_axis_plane_lateral_property(ScriptVariant **varlist, int paramCount)
{
    #define ARG_MINIMUM     2   // Minimum number of arguments allowed in varlist.
    #define ARG_PROPERTY    1   // Varlist element carrying which property is requested.

    char *propname = NULL;  // Placeholder for string property name from varlist.
    int prop;               // Placeholder for integer constant located by string.

    static const char *proplist[] =
    {
        "x",
        "z"
    };

    // If the minimum argument count
    // was not passed, then there is
    // nothing to map. Return true - we'll
    // catch the mistake in property access
    // functions.
    if(paramCount < ARG_MINIMUM)
    {
        return 1;
    }

    // See macro - will return 0 on fail.
    MAPSTRINGS(varlist[ARG_PROPERTY], proplist, _AXIS_PLANE_LATERAL_END,
               "Property name '%s' is not supported by axis lateral plane.\n");


    // If we made it this far everything should be OK.
    return 1;

    #undef ARG_MINIMUM
    #undef ARG_PROPERTY
}

// Use string property argument to find an
// integer property constant and populate
// varlist->lval.
int mapstrings_axis_plane_vertical_property(ScriptVariant **varlist, int paramCount)
{
    #define ARG_MINIMUM     2   // Minimum number of arguments allowed in varlist.
    #define ARG_PROPERTY    1   // Varlist element carrying which property is requested.

    char *propname = NULL;  // Placeholder for string property name from varlist.
    int prop;               // Placeholder for integer constant located by string.

    static const char *proplist[] =
    {
        "x",
        "y"
    };

    // If the minimum argument count
    // was not passed, then there is
    // nothing to map. Return true - we'll
    // catch the mistake in property access
    // functions.
    if(paramCount < ARG_MINIMUM)
    {
        return 1;
    }

    // See macro - will return 0 on fail.
    MAPSTRINGS(varlist[ARG_PROPERTY], proplist, _AXIS_PLANE_VERTICAL_END,
               "Property name '%s' is not supported by axis vertical plane.\n");


    // If we made it this far everything should be OK.
    return 1;

    #undef ARG_MINIMUM
    #undef ARG_PROPERTY
}

// Use string property argument to find an
// integer property constant and populate
// varlist->lval.
int mapstrings_axis_principal_property(ScriptVariant **varlist, int paramCount)
{
    #define ARG_MINIMUM     2   // Minimum number of arguments allowed in varlist.
    #define ARG_PROPERTY    1   // Varlist element carrying which property is requested.

    char *propname = NULL;  // Placeholder for string property name from varlist.
    int prop;               // Placeholder for integer constant located by string.

    static const char *proplist[] =
    {
        "x",
        "y",
        "z"
    };

    // If the minimum argument count
    // was not passed, then there is
    // nothing to map. Return true - we'll
    // catch the mistake in property access
    // functions.
    if(paramCount < ARG_MINIMUM)
    {
        return 1;
    }

    // See macro - will return 0 on fail.
    MAPSTRINGS(varlist[ARG_PROPERTY], proplist, _AXIS_PRINCIPAL_END,
               "Property name '%s' is not supported by axis principal.\n");


    // If we made it this far everything should be OK.
    return 1;

    #undef ARG_MINIMUM
    #undef ARG_PROPERTY
}

// Caskey, Damon  V.
// 2018-05-14
//
// Return an axis property. Requires
// the handle from axis property
// and property name to access.
HRESULT openbor_get_axis_plane_lateral_float_property(ScriptVariant **varlist , ScriptVariant **pretvar, int paramCount)
{
    #define SELF_NAME       "openbor_get_axis_plane_lateral_float_property(void handle, char property)"
    #define ARG_MINIMUM     2   // Minimum required arguments.
    #define ARG_HANDLE      0   // Handle (pointer to property structure).
    #define ARG_PROPERTY    1   // Property to access.

    s_axis_plane_lateral_float      *handle     = NULL; // Property handle.
    e_axis_plane_lateral_properties property    = 0;    // Property argument.

    // Clear pass by reference argument used to send
    // property data back to calling script.     .
    ScriptVariant_Clear(*pretvar);

    // Map string property name to a
    // matching integer constant.
    mapstrings_axis_plane_lateral_property(varlist, paramCount);

    // Verify arguments. There should at least
    // be a pointer for the property handle and an integer
    // to determine which property constant is accessed.
    if(paramCount < ARG_MINIMUM
       || varlist[ARG_HANDLE]->vt != VT_PTR
       || varlist[ARG_PROPERTY]->vt != VT_INTEGER)
    {
        *pretvar = NULL;
        goto error_local;
    }
    else
    {
        // Populate local vars for readability.
        handle      = (s_axis_plane_lateral_float *)varlist[ARG_HANDLE]->ptrVal;
        property    = (LONG)varlist[ARG_PROPERTY]->lVal;
    }

    // All values are float (DOUBLE) type.
    ScriptVariant_ChangeType(*pretvar, VT_DECIMAL);

    switch(property)
    {
        case _AXIS_PLANE_LATERAL_X:

            (*pretvar)->dblVal = (DOUBLE)handle->x;

            break;

        case _AXIS_PLANE_LATERAL_Z:

            (*pretvar)->dblVal = (DOUBLE)handle->z;

            break;

        default:

            printf("Unsupported property.\n");
            goto error_local;

            break;
    }

    return S_OK;

    error_local:

    printf("You must provide a valid handle and property name: " SELF_NAME "\n");
    *pretvar = NULL;

    return E_FAIL;

    #undef SELF_NAME
    #undef ARG_MINIMUM
    #undef ARG_HANDLE
    #undef ARG_INDEX
}

// Caskey, Damon  V.
// 2018-05-14
//
// Mutate an axis property. Requires
// the handle from axis property, property
// name to modify, and the new value.
HRESULT openbor_set_axis_plane_lateral_float_property(ScriptVariant **varlist, ScriptVariant **pretvar, int paramCount)
{
    #define SELF_NAME           "openbor_set_axis_plane_lateral_float_property(void handle, char property, value)"
    #define ARG_MINIMUM         3   // Minimum required arguments.
    #define ARG_HANDLE          0   // Handle (pointer to property structure).
    #define ARG_PROPERTY        1   // Property to access.
    #define ARG_VALUE           2   // New value to apply.

    int                             result      = S_OK; // Success or error?
    s_axis_plane_lateral_float      *handle     = NULL; // Property handle.
    e_axis_plane_lateral_properties property    = 0;    // Property to access.

    // Value carriers to apply on properties after
    // taken from argument.
    float         temp_float;

    // Map string property name to a
    // matching integer constant.
    mapstrings_axis_plane_lateral_property(varlist, paramCount);

    // Verify incoming arguments. There should at least
    // be a pointer for the property handle and an integer
    // to determine which property is accessed.
    if(paramCount < ARG_MINIMUM
       || varlist[ARG_HANDLE]->vt != VT_PTR
       || varlist[ARG_PROPERTY]->vt != VT_INTEGER)
    {
        *pretvar = NULL;
        goto error_local;
    }

    // Populate local handle and property vars.
    handle      = (s_axis_plane_lateral_float *)varlist[ARG_HANDLE]->ptrVal;
    property    = (LONG)varlist[ARG_PROPERTY]->lVal;

    // All values are same type for this property set,
    // so we can copy to temp var right here.
    if(!SUCCEEDED(ScriptVariant_DecimalValue(varlist[ARG_VALUE], &temp_float)))
    {
        goto error_local;
    }

    // Which property to modify?
    switch(property)
    {

        case _AXIS_PLANE_LATERAL_X:

            handle->x = temp_float;

            break;

        case _AXIS_PLANE_LATERAL_Z:

            handle->z = temp_float;

            break;

        default:

            printf("Unsupported property.\n");
            goto error_local;

            break;
    }

    return result;

    // Error trapping.
    error_local:

    printf("You must provide a valid binding handle, property, and new value: " SELF_NAME "\n");

    result = E_FAIL;
    return result;

    #undef SELF_NAME
    #undef ARG_MINIMUM
    #undef ARG_HANDLE
    #undef ARG_PROPERTY
    #undef ARG_VALUE
}
