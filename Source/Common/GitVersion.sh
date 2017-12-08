#!/bin/bash

GITHASH=`git log --pretty=format:"%H" -1`
GITHASHSHORT=`git log --pretty=format:"%h" -1`
GITDATE=`git log --pretty=format:"%cd" -1`
GITROLLINGCOUNT=`git log --pretty=format:'' | wc -l`
GITHEADER=$1
PROJECT=`echo $2 | awk '{print toupper( $0 )}'`

TAG_NAME=`git describe --tags | sed -e 's/_[0-9].*//'`
VERSION_NUM=`git describe --match "${TAG_NAME}_[0-9]*" HEAD | sed -e 's/-g.*//' -e "s/${TAG_NAME}_//"`
MAJOR_BUILD_NUM=`echo $VERSION_NUM | sed 's/-[^.]*$//' | sed -r 's/.[^.]*$//' | sed -r 's/.[^.]*$//'`
MINOR_BUILD_NUM=`echo $VERSION_NUM | sed 's/-[^.]*$//' | sed -r 's/.[^.]*$//' | sed -r 's/.[.]*//'`
REVISION_BUILD_NUM=`echo $VERSION_NUM | sed 's/-[^.]*$//' | sed -r 's/.*(.[0-9].)//'`
BUILD_NUM=`echo $VERSION_NUM | sed -e 's/[0-9].[0-9].[0-9]//' -e 's/-//'`
BRANCH=`git rev-parse --abbrev-ref HEAD`

printf "Generating $2 Git Version Header...\n"
printf "Revision: $GITROLLINGCOUNT [$GITHASH] $GITDATE\n"

printf "#ifndef __%s_GITVERSION_HPP__\n" $PROJECT > $GITHEADER
printf "#define __%s_GITVERSION_HPP__\n\n" $PROJECT >> $GITHEADER

printf "#define GIT_COMMITHASH			\"%s\"\n" "$GITHASH" >> $GITHEADER
printf "#define GIT_COMMITHASHSHORT		\"%s\"\n" "$GITHASHSHORT" >> $GITHEADER
printf "#define GIT_COMMITTERDATE		\"%s\"\n" "$GITDATE" >> $GITHEADER
printf "#define GIT_ROLLINGCOUNT		%d\n\n" $GITROLLINGCOUNT >> $GITHEADER

printf "#define GIT_MAJOR_BUILD_VERSION		%d\n" $MAJOR_BUILD_NUM >> $GITHEADER
printf "#define GIT_MINOR_BUILD_VERSION		%d\n" $MINOR_BUILD_NUM >> $GITHEADER
printf "#define GIT_REVISION_BUILD_NUM		%d\n" $REVISION_BUILD_NUM >> $GITHEADER
printf "#define GIT_BUILD_NUM				%d\n" $BUILD_NUM >> $GITHEADER
printf "#define GIT_BUILD_VERSION			\"%d.%d.%d.%d\"\n" $MAJOR_BUILD_NUM $MINOR_BUILD_NUM $REVISION_BUILD_NUM $BUILD_NUM >> $GITHEADER
printf "#define GIT_TAG_NAME				\"%s\"\n" $TAG_NAME >> $GITHEADER
printf "#define GIT_BRANCH					\"%s\"\n\n" $BRANCH >> $GITHEADER
printf "#endif\n" >> $GITHEADER

printf "Done\n"
