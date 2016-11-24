#!/bin/sh
##
## makeclase.sh
## Login : <mcm014es@localhost.localdomain>
## Started on  Mon Apr 10 16:09:12 2006 
## $Id$
## 
## Copyright (C) 2006 
## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2 of the License, or
## (at your option) any later version.
## 
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
## 
## You should have received a copy of the GNU General Public License
## along with this program; if not, write to the Free Software
## Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
##

CABECERA=""
CUERPO=""
CLASE=""

function uso ()
{
    echo $0
    echo "Opciones:"
    echo "--help"
    echo "-c|--cabecera <tipo clase>"
    echo "-b|--cuerpo <tipo clase>"
    echo "--clase <nombre>"

}


while [ "$1" != "" ]
do
  echo $1
  case $1 in
      --help)
	  uso
	  exit 0
	  ;;
      -c|--cabecera)
	  shift
	  CABECERA=$1
	  ;;
      -b|--cuerpo)
	  shift
	  CUERPO=$1
	  ;;
      --clase)
	  shift
	  CLASE=$1
	  ;;
      *)
	  uso
	  exit 1
	  ;;
  esac
  shift
done

if [ "$CABECERA" == "" ]; then
    echo "Ha de facilitar un tipo de clase para la cabecera (.hh)."
    exit 2
fi

if [ "$CUERPO" == "" ]; then
    echo "Ha de facilitar un tipo de clase para el cuerpo (.cc)."
    exit 3
fi

if [ "$CLASE" == "" ]; then
    echo "Ha de facilitar un nombre de clase."
    exit 4
fi

echo "Creando la clase $CLASE."
./genclas --tipo-clase=$CABECERA --clase=$CLASE > $CLASE.hh
./genclas --tipo-clase=$CUERPO --clase=$CLASE > $CLASE.cc
