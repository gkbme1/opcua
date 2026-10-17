#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/GTIODriverModbusTCPMaster.o \
	${OBJECTDIR}/ModbusTCPFrame.o \
	${OBJECTDIR}/ModbusTCPMaster.o \
	${OBJECTDIR}/ModbusTCPSlave.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L../../bin -lOpenLib -lPrivateUtilLib

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../../bin/libGTIODriverModbusTCPMaster.${CND_DLIB_EXT}

../../bin/libGTIODriverModbusTCPMaster.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ../../bin
	${LINK.cc} -o ../../bin/libGTIODriverModbusTCPMaster.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -fPIC -shared -fPIC

${OBJECTDIR}/GTIODriverModbusTCPMaster.o: GTIODriverModbusTCPMaster.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DGTIODRIVERMODBUSMASTER_EXPORTS -I../../OpenInclude -I../../Include -I../../OpenInclude/lua-5.1.4_src -I../../NetBase -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GTIODriverModbusTCPMaster.o GTIODriverModbusTCPMaster.cpp

${OBJECTDIR}/ModbusTCPFrame.o: ModbusTCPFrame.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DGTIODRIVERMODBUSMASTER_EXPORTS -I../../OpenInclude -I../../Include -I../../OpenInclude/lua-5.1.4_src -I../../NetBase -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ModbusTCPFrame.o ModbusTCPFrame.cpp

${OBJECTDIR}/ModbusTCPMaster.o: ModbusTCPMaster.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DGTIODRIVERMODBUSMASTER_EXPORTS -I../../OpenInclude -I../../Include -I../../OpenInclude/lua-5.1.4_src -I../../NetBase -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ModbusTCPMaster.o ModbusTCPMaster.cpp

${OBJECTDIR}/ModbusTCPSlave.o: ModbusTCPSlave.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -DGTIODRIVERMODBUSMASTER_EXPORTS -I../../OpenInclude -I../../Include -I../../OpenInclude/lua-5.1.4_src -I../../NetBase -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ModbusTCPSlave.o ModbusTCPSlave.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ../../bin/libGTIODriverModbusTCPMaster.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
