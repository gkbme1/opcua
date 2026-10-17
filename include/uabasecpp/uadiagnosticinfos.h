/******************************************************************************
** uadiagnosticinfos.h
**
** Copyright (c) 2006-2020 Unified Automation GmbH. All rights reserved.
**
** Software License Agreement ("SLA") Version 2.7
**
** Unless explicitly acquired and licensed from Licensor under another
** license, the contents of this file are subject to the Software License
** Agreement ("SLA") Version 2.7, or subsequent versions
** as allowed by the SLA, and You may not copy or use this file in either
** source code or executable form, except in compliance with the terms and
** conditions of the SLA.
**
** All software distributed under the SLA is provided strictly on an
** "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
** AND LICENSOR HEREBY DISCLAIMS ALL SUCH WARRANTIES, INCLUDING WITHOUT
** LIMITATION, ANY WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
** PURPOSE, QUIET ENJOYMENT, OR NON-INFRINGEMENT. See the SLA for specific
** language governing rights and limitations under the SLA.
**
** The complete license agreement can be found here:
** http://unifiedautomation.com/License/SLA/2.7/
**
** Project: C++ OPC SDK base module
**
** Portable UaDiagnosticInfos class.
**
******************************************************************************/
#ifndef UADIAGNOSTICINFOS_H
#define UADIAGNOSTICINFOS_H

#include <opcua_proxystub.h>

#include "uabase.h"
#include "uaarraytemplates.h"

/** Class for managing an array of DiagnosticInfo structures
*/
class UABASE_EXPORT UaDiagnosticInfos
{
public:
    UaDiagnosticInfos();
    UaDiagnosticInfos(const UaDiagnosticInfos &other);
    UaDiagnosticInfos(OpcUa_Int32 length, OpcUa_DiagnosticInfo* data);
    virtual ~UaDiagnosticInfos();

    UaDiagnosticInfos& operator=(const UaDiagnosticInfos &other);
    OpcUa_DiagnosticInfo& operator[](const OpcUa_UInt32 index) const;

    bool operator==(const UaDiagnosticInfos &other) const;
    bool operator!=(const UaDiagnosticInfos &other) const;

    void attach(OpcUa_UInt32 length, OpcUa_DiagnosticInfo* data);
    void attach(OpcUa_Int32 length, OpcUa_DiagnosticInfo* data);
    OpcUa_DiagnosticInfo* detach();

    void create(OpcUa_UInt32 length);
    void resize(OpcUa_UInt32 length);
    void clear();

    void attachStringTable(OpcUa_Int32 uNoOfStringTable, OpcUa_String *pStringTable);
    OpcUa_String* detachStringTable();

    /** Returns size of the string table used for the DiagnosticInfo structures.
    *
    * The string table is only set if the class UaDiagnosticInfos is not used in a context
    * where the string table is already provided in other parameters.
    */
    OpcUa_UInt32 noOfStringTable() const;

    /** Get the string for an index in the DiagnosticInfo
    *
    * The caller must check if the indes is smaller than the size of the string table
    * provide through noOfStringTable.
    */
    const OpcUa_String& stringTableAt(OpcUa_UInt32 index) const;

    /** Length of the DiagnosticInfo structure array */
    inline OpcUa_UInt32 length() const {return m_noOfElements;}
    /** Returns the raw data for the DiagnosticInfo structure array */
    inline OpcUa_DiagnosticInfo* rawData() const {return m_data;}

private:
    OpcUa_UInt32 m_noOfElements;
    OpcUa_DiagnosticInfo* m_data;

    UaStringArray m_stringTable;
};

#endif // UADIAGNOSTICINFOS_H

