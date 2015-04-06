__author__ = 'ee364g07'
import base64
from PIL import Image
import re
import math


class Message:
    types = ['Text', 'GrayImage', 'ColorImage']

    def __init__(self, **kwargs):
        """
        creates an instance of message, does error checks for if the right amount of arguments are given,
        if the correct message type is input and if the XML string given is empty
        :param kwargs:
        :return:
        """
        ksize = len(kwargs.keys())
        if ksize == 2:
            for val in kwargs.values():
                if val == "":
                    raise ValueError("Missing an argument!")
            if kwargs.get('messageType') in self.types:
                self.messageType = kwargs.get('messageType')
            else:
                raise TypeError("Wrong message type!")
            self.filePath = kwargs.get("filePath")
            self.XmlString = self.getXmlString()
        else:
            if "XmlString" not in kwargs.keys():
                raise ValueError
            else:
                self.XmlString = kwargs.get("XmlString")
                if self.XmlString == "":
                    raise ValueError
                else:
                    pat = r'<message type="(.*?)"'
                    match = re.search(pat, self.XmlString)
                    if match:
                        self.messageType = match.group(1)
                        if self.messageType != 'Text':
                            h,v = (self.findimagesize())
                            self.sizeof = (int(h),int(v))
                    else:
                        ValueError("no type!")

    def findimagesize(self):
        """
        finds the dimension of the image, given the xml information of the image

        """
        str = self.XmlString
        pat = r'size="(.*),(.*)"\s'
        match = re.search(pat, str)
        if match:
            return match.group(1),match.group(2)
        else:
            return None

    def findmessage(self):
        """
        finds the base64 encoded message in the XML string using a reg-ex

        """
        str = self.XmlString
        pat = r'>\n(.*?)\n</message>'
        match = re.search(pat, str)
        try:
            if match:
                return match.group(1)
        except ValueError:
            print("No data exists!")

    def text2xml(self):
        """
        changes the content of the text file to base64, encodes it and places it in the XML file


        """
        with open(self.filePath, 'r') as file:
            content = file.read()
        encoded = base64.b64encode(bytes(content, 'UTF-8'))
        encoded = str(encoded, "UTF-8")
        return '<?xml version="1.0" encoding="UTF-8"?>\n<message type="{2}" size="{0}" encrypted="False">\n{1}\n</message>'.format(len(content), encoded, self.messageType)

    def image2xml(self):
        """
        converts the content of a gray-scale image to base64, encodes it and places it an XML file

        """
        im = Image.open(self.filePath)
        rscan = list(im.getdata())
        h,v = im.size
        self.sizeof = (h,v)
        self.size = "{0},{1}".format(h,v)
        encoded = base64.b64encode(bytes(rscan))
        encoded = str(encoded, "UTF-8")
        return '<?xml version="1.0" encoding="UTF-8"?>\n<message type="{2}" size="{0}" encrypted="False">\n{1}\n</message>'.format(self.size, encoded, self.messageType)

    def cimage2xml(self):
        """
        converts the contents of a color image to base64, encodes it and places it in an XML file

        """
        im = Image.open(self.filePath)
        rscan = list(im.getdata(band = 0))
        gscan = list(im.getdata(band = 1))
        bscan = list(im.getdata(band = 2))
        h,v = im.size #horizontal and vertical
        self.sizeof = (h,v)
        self.size = "{0},{1}".format(h,v)
        test = rscan + gscan + bscan
        encoded = base64.b64encode(bytes(test))
        encoded = str(encoded, "UTF-8")
        return '<?xml version="1.0" encoding="UTF-8"?>\n<message type="{2}" size="{0}" encrypted="False">\n{1}\n</message>'.format(self.size, encoded, self.messageType)

    def getXmlString(self):
        """
        gets the XML string of the message depending on what type of message is being encoded

        """
        if self.messageType == "Text":
           return self.text2xml()
        elif self.messageType == "GrayImage":
            return self.image2xml()
        elif self.messageType == "ColorImage":
            return self.cimage2xml()

    def getMessageSize(self):
        """
        gets the size of the XML version of the image

        """
        size = len(self.XmlString)
        if size == 0:
            raise ValueError("No data exists!")
        else:
            return size

    def saveToImage(self, targetImagePath):
        """
        Decodes the base64 version of the Image, converts it into an Image and saves the Image created to
        the Image Path given
        :param targetImagePath:
        :return:
        """
        if self.messageType == 'Text':
            raise TypeError("Wrong type!")
        elif self.messageType == 'GrayImage':
            dcode = self.findmessage()
            img = base64.b64decode(bytes(dcode, 'UTF-8'))
            im = Image.frombytes('L', self.sizeof, img)
            im.save(targetImagePath)
        elif self.messageType == 'ColorImage':
            dcode = self.findmessage() #gets the b64 encoded message as a string
            img = base64.b64decode(bytes(dcode,'UTF-8')) #this changes it to bytes then decodes it
            list_of_pixels = list(img) #this give raster scan array
            size = len(list_of_pixels) #size of the sequenced array
            red = list_of_pixels[0:int(size/3)]
            green = list_of_pixels[int(size/3):int(2*size/3)]
            blue = list_of_pixels[int(2*size/3):]
            RGB = [(r,g,b) for r,g,b in zip(red,green,blue)] #list comprehension to create a list of tuple in RGB format
            im2 = Image.new('RGB', self.sizeof)
            im2.putdata(RGB)
            im2.save(targetImagePath)

    def saveToTextFile(self, targetTextFilePath):
        """
        Decodes the base64 version of the Text given converts it into a UTF-8 text file, and saves to the filepath given
        :param targetTextFilePath:
        :return:
        """
        if self.messageType != 'Text':
            raise TypeError("Wrong type!")
        else:
            dcode = self.findmessage()
            msg = base64.b64decode(bytes(dcode, "UTF-8"))
            msg = str(msg, "UTF-8")
            with open(targetTextFilePath, 'w') as fill:
                fill.write(msg)

    def saveToTarget(self, targetPath):
        """
        saves the message to a target path dependent on what type the message is
        :param targetPath:
        :return:
        """
        if self.messageType == 'Text':
            self.saveToTextFile(targetPath)
        elif self.messageType == 'ColorImage' or self.messageType == 'GrayImage':
            self.saveToImage(targetPath)

class Steganography:
    directions = ['horizontal', 'vertical']

    def __init__(self, imagePath, direction='horizontal'):
        """
        creates an instance of steganography checks if direction given exists, checks if the Image
        given is a gray-scale Image. Uses the data given and creates an image scanned with the direction given
         and saves it to the Image Path given
        :param imagePath:
        :param direction:
        :return:
        """
        if direction not in self.directions:
            raise ValueError('No such direction!')
        else:
            self.direction = direction
        im = Image.open(imagePath)
        if im.mode != 'L':
            raise TypeError("Image must be a gray-scale Image!")
        else:
            self.imagePath = imagePath #medium for embedded message
            im = Image.open(imagePath)
            h,v = im.size
            self.size = (h,v)
            self.maxmessagesize = int(h) * int(v)
            self.pixels_medium = self.getdirectiondata(self.direction)

    def getdirectiondata(self, direction):
        """
        raster scans the image based on the direction given
        """
        im = Image.open(self.imagePath)
        if direction == 'horizontal':
            return list(im.getdata())
        elif direction == 'vertical':
            new = im.transpose(Image.TRANSPOSE)
            h,v = new.size
            self.size = (h,v)
            return list(new.getdata())

    def getbitstream(self, number):
        """
        converts the ascii version of the pixel to binary and gives the bits in the
        stream as a list
        :param number:
        :return:
        """
        new = []
        i = 2
        num = int(number)
        for digit in range(9,17):
            pwr = digit - i
            its = num & int(math.pow(2, pwr))
            if its != 0:
                its /= its
                new.append(int(its))
            else:
                new.append(int(its))
            i += 2
        return new

    def forcezero(self, num):
        """
        changes the last bit of a digit to zero

        :param num:
        :return:
        """
        a = bin(num & 254)
        return int(a, 2)

    def forceone(self, num):
        """
        changes the last bit of a digit to one
        """
        a = bin(num | 1)
        return int(a, 2)


    def embedMessageInMedium(self, message, targetImagePath):
        """
        embeds the message given into the medium, and saves the new medium
        embedded with a message to the targetImage Path given

        :param message:
        :param targetImagePath:
        :return:
        """
        if message.getMessageSize() * 8 > self.maxmessagesize:
            raise ValueError("Message to embed is too Large!")
        else:
            data2embed = message.getXmlString()
            pixel2embed = [ord(ch) for ch in data2embed]
            ogpixels = self.pixels_medium
            newpixel = []
            current = 0         #message character control variable
            lcv = 0             #bit loop control variable
            ocv = 1             #new pixels control variable
            messagepixel = pixel2embed[current]
            bits = self.getbitstream(messagepixel)
            lenembed = len(pixel2embed)

            for pixel in ogpixels:
                if ocv >= (lenembed * 8) + 1:
                    newpixel.append(pixel)
                    ocv+=1
                else:
                    if lcv == 8 and current < (lenembed -1):
                        lcv = 0
                        current += 1
                        messagepixel = pixel2embed[current]
                        bits = self.getbitstream(messagepixel)
                        if bits[lcv] == 0:
                            new_pixel = self.forcezero(pixel)
                            newpixel.append(new_pixel)
                            lcv+=1
                        elif bits[lcv] == 1:
                            new_pixel = self.forceone(pixel)
                            newpixel.append(new_pixel)
                            lcv+=1
                    elif lcv == 8 and current == (lenembed - 1):
                        break
                    else:
                        if bits[lcv] == 0:
                            new_pixel = self.forcezero(pixel)
                            newpixel.append(new_pixel)
                            lcv+=1
                        elif bits[lcv] == 1:
                            new_pixel = self.forceone(pixel)
                            newpixel.append(new_pixel)
                            lcv+=1
                ocv += 1

            if self.direction == 'horizontal':

                image = Image.new('L', self.size)
                image.putdata(newpixel)
                image.save(targetImagePath)
            elif self.direction == 'vertical':

                image = Image.new('L', self.size)
                image.putdata(newpixel)
                new = image.transpose(Image.TRANSPOSE)
                new.save(targetImagePath)

    def bits2data(self, byte):
        """
        converts from binary to ASCII

        :param byte:
        :return:
        """
        pwrs = [7,6,5,4,3,2,1,0]
        total = sum([(y * math.pow(2, x)) for x, y in zip(pwrs, byte)])
        return int(total)

    def extractMessageFromMedium(self):
        """
        extracts XML data from the medium given the scanning direction
        uses the XML data extracted to create a message instance

        :return:
        """
        self.pixels_medium = self.getdirectiondata(self.direction)
        messagelist = []
        data = []
        lcv = 0
        for pixel in self.pixels_medium:
            if lcv == 8:
                encpixel = (self.bits2data(data))
                messagelist.append(chr(encpixel))
                data = []
                lcv = 0
                if pixel % 2 == 0:
                    data.append(0)
                    lcv += 1
                else:
                    data.append(1)
                    lcv += 1
            else:
                if pixel % 2 == 0:
                    data.append(0)
                    lcv += 1
                else:
                    data.append(1)
                    lcv += 1
        messagestring = "".join(messagelist)
        if self.findxmlstring(messagestring) != None:
            return Message(XmlString=self.findxmlstring(messagestring))
        else:
            return

    def findxmlstring(self, fullstring):
        """
        finds the xml data in the decrypted data
        :param fullstring:
        :return:
        """
        str = fullstring
        pat = r'(\<\?xml.*?)\n.*\n.*\n..........'
        match = re.search(pat, str)
        if match:
                return match.group()
        else:
            return



if __name__ == "__main__":
    pass
