import urllib2
import re
import sys
import locale

def openurl(urlname):
    urlreq    = urllib2.Request(urlname)
    browse  = 'Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.0)'
    uopener = urllib2.build_opener()
    urlreq.add_header('User-Agent', browse)
    try:
        gdurl   = uopener.open(urlreq)
        return gdurl
    except Exception as e:
        print "Error opening URL:", urlname, "\nException:", e

    return None


def geturls(urlname):
    URLs = {}
    descri  = openurl(urlname)
    if not descri:
        print "Error opening URL:", urlname
        return URLs

    # Only htm(l) extensions.
    # www.google.com won't be accepted - no "/" at the end.
    # Also, we DO need http.
    urlp  = re.compile('(http:\/\/.+)(.+\.(htm.?|com|info|de|php|stm))?(\/)?', re.IGNORECASE)
    urltp = re.compile('<a (?:.*?)href="(\S*?)">(.*?)</a>', re.DOTALL)

    # To know if the address is absolute or relative
    m = urlp.match(urlname)
    if m == None:
        return URLs
    stem = m.group(1)

    lines = descri.read().replace('\n', ' ')
    urltags = urltp.findall(lines)
    for eachurl in urltags:
        if urlp.match(eachurl[0]):
            URLs[eachurl[0]] = {"Description":eachurl[1]}
        else :
            URLs[stem + eachurl[0]] = {"Description":eachurl[1]}

    descri.close()
    return URLs


GlobalUrlList = {}
def crawlurl(fromurl, urlname, description, depth):
    if not depth:
        return

    if GlobalUrlList.has_key(urlname):
        GlobalUrlList[urlname]["Visited"] += 1
        GlobalUrlList[urlname]["From"]    += [fromurl]
        return

    print urlname

    subUrls = geturls(urlname);

    GlobalUrlList[urlname] = {"Description":description,
            "Visited":1, "From":[fromurl]}

    for eachurl in subUrls:
        crawlurl(urlname, eachurl, subUrls[eachurl]["Description"], depth - 1)

import sys
def main(args):
    if len(args) != 3:
        print """Usage: <urlmanager> <OPTION> <urlname>

        <urlname> MUST have the protocol type (http) in it.

        OPTIONS:
            open      - prints the remote file
            geturls   - get the urls inside the remote file
            crawl     - crawls the urls upto a depth of 2"""
    else:
        if args[1] == 'open':
            x = openurl(args[2])
            if x:
                print x.read()
        if args[1] == 'geturls':
            for x in geturls(args[2]):
                print x
        if args[1] == 'crawl':
            crawlurl('<>', args[2], '<>', 2)
            for x in GlobalUrlList.iterkeys():
                print x

if __name__ == '__main__':
    main(sys.argv)
