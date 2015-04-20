__author__ = 'ee364g07'
# $Author: ee364g07 $
# $Date: 2015-04-20 15:54:28 -0400 (Mon, 20 Apr 2015) $
# $Revision: 79275 $
# $HeadURL: svn+ssh://ece364sv@ecegrid-thin1/home/ecegrid/a/ece364sv/svn/S15/students/ee364g07/Lab11/NewSteganography.py $
# $Id: NewSteganography.py 79275 2015-04-20 19:54:28Z ee364g07 $

import base64
from PIL import Image
import re
import math
from Steganography import *

class NewSteganography(Steganography):

    def __init__(self, imagePath, direction='horizontal'):
        Steganography.__init__(self, imagePath, direction)

    def wipeMedium(self):
        new_pixel = []
        for oldpixel in self.pixels_medium:
            newpixel = self.forcezero(oldpixel)
            new_pixel.append(newpixel)
        self.embedbydirection(self.direction, new_pixel,self.imagePath)

    def checkIfMessageExists(self):
        mediumdata = []
        message = []
        bcv = 0
        ocv = 0
        for pixel in self.pixels_medium:
            if ocv > 64:
                break
            if bcv == 8:
                encodedpixel = (self.bits2data(message))                   #converts the bits value to an ASCII representation of the character
                mediumdata.append(chr(encodedpixel))
                ocv += 1
                bcv = 0                                                 #reset bit counter
                message = []                                            #reset messagelist
                message.append(self.getlsb(pixel))
                bcv += 1
            else:
                message.append(self.getlsb(pixel))
                bcv += 1

        mediumstring = "".join(mediumdata)

        str = mediumstring
        pat = r'<?.*?type="(.*)"'
        match = re.search(pat, str)

        if match:
            return True,match.group(1)
        else:
            return False, None




if __name__ == "__main__":
    #b = Steganography('files/tiger_lena_h.png', 'horizontal')
    c = NewSteganography('files/grays/bridge.png', 'horizontal')
    print(c.checkIfMessageExists())

