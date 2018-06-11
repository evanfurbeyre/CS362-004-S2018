

import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
	   UrlValidator validator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   System.out.println("Running Manual Tests (8 total).");
	   
	   System.out.println("http://www.amazon.com Valid? " + validator.isValid("http://www.amazon.com"));
	   System.out.println("http://www.amazon.co Valid? " + validator.isValid("http://www.amazon.co"));
	   System.out.println("http://www.amazon.cm Valid? " + validator.isValid("http://www.amazon.cm"));
	   System.out.println("http://www.google.com Valid? " + validator.isValid("http://www.google.com"));
	   System.out.println("file://C:/Users/admin/Document Valid? " + validator.isValid("file://C:/Users/admin/Document"));
	   System.out.println("ftp://ftp.test/filefolder/somethinng.txt Valid? " + validator.isValid("ftp://ftp.test/filefolder/somethinng.txt"));
	   System.out.println("sometext Valid? " + validator.isValid("sometext"));
	   System.out.println("http://www.text.net# Valid? " + validator.isValid("http://www.text.net#"));
   }
   
   
   public void testYourFirstPartition()
   {
	   UrlValidator validator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   System.out.println("Running First Partition Test on Schemes.");
	   
	   String temp;
	   
	   for(int i  = 0; i < 10; i++)
	   {
		   for(int j = 0; j < 10; j++)
		   {
			   for(int k = 0; k < 10; k++)
			   {
				   for(int l = 0; l < 10; l++)
				   {
					   for(int m = 0; m < 10; m++)
					   {
						   
						   temp = p1Schemes[i] + p1Authorities[j] + p1Ports[k] + p1Paths[l] + p1Queries[m];
						   System.out.println(temp + " is " + validator.isValid(temp));
						   System.out.println();
					   }
				   }
			   }
		   }
	   }
	   
	   System.out.println(validator.isValid("http://www.letsmakeareallylongurltotestthefirstpartitiontestermethodwithinincorrect.net"));
   }
   
   public void testYourSecondPartition()
   {
	   UrlValidator validator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   System.out.println("Running Second Partition Test on Ports.");
	   
	   String temp;
	   
	   for(int i  = 0; i < 10; i++)
	   {
		   for(int j = 0; j < 10; j++)
		   {
			   for(int k = 0; k < 10; k++)
			   {
				   for(int l = 0; l < 10; l++)
				   {
					   for(int m = 0; m < 10; m++)
					   {
						   
						   temp = p2Schemes[i] + p2Authorities[j] + p2Ports[k] + p2Paths[l] + p2Queries[m];
						   System.out.println(temp + " is " + validator.isValid(temp));
						   System.out.println();
					   }
				   }
			   }
		   }
	   }
   } 
   
   //Some invalid entries for partition testing
   static String[] p1Schemes = {
		   "",
		   "http://",
		   "h://",
		   "http11://",
		   "http:",
		   "http:/",
		   "htnteepee-://",
		   "h.://",
		   "ftp://",
		   ".http://",
   };
   
   static String[] p1Authorities = {
		   "www.google.com",
		   "google.com",
		   "google.net",
		   "255.255.255.255",
		   "1.2.232.83",
		   "www.goo-le.biz",
		   "www.google.cu",
		   "9.2.4.4",
		   "localhost",
		   "www.google.org"
   };
   
   static String[] p1Ports = {
		   ":11111",
		   ":0999",
		   ":097",
		   ":12",
		   ":5",
		   ":19483",
		   ":3938",
		   ":800",
		   ":89",
		   ""
   };
   
   static String[] p1Paths = {
		   "",
		   "/destination",
		   "/7495860",
		   "/9",
		   "/s",
		   "/:blue42omaha/~*#&$)",
		   "/destination/",
		   "/destination/destination",
		   "/destination",
		   "/"
   };
   
   static String[] p1Queries = {
		   "",
		   "?",
		   "?something",
		   "??",
		   "?11",
		   "?p5",
		   "?questionmark",
		   "?mode=read",
		   "?mode=read&status=0",
		   "?mode="
   };
   
   static String[] p2Schemes = {
		   "",
		   "http://",
		   "h://",
		   "http11://",
		   "ht3p://",
		   "htt+://",
		   "htnteepee-://",
		   "h.://",
		   "ftp://",
		   "fteepee://"
   };
   
   static String[] p2Authorities = {
		   "www.google.com",
		   "google.com",
		   "google.net",
		   "255.255.255.255",
		   "1.2.232.83",
		   "www.goo-le.biz",
		   "www.google.cu",
		   "9.2.4.4",
		   "localhost",
		   "www.google.org"
   };
   
   //Some invalid entries for partition testing
   static String[] p2Ports = {
		   ":11111",
		   ":0999",
		   ":097",
		   ":12",
		   ":5",
		   ":19483",
		   ":3938",
		   ":800",
		   ":89",
		   ""
   };
   
   static String[] p2Paths = {
		   "",
		   "/destination",
		   "/7495860",
		   "/9",
		   "/s",
		   "/:blue42omaha/~*#&$)",
		   "/destination/",
		   "/destination/destination",
		   "/destination",
		   "/"
   };
   
   static String[] p2Queries = {
		   "",
		   "?",
		   "?something",
		   "??",
		   "?11",
		   "?p5",
		   "?questionmark",
		   "?mode=read",
		   "?mode=read&status=0",
		   "?mode="
   };
  
  public static void main(String[] argv) {

	   UrlValidatorTest testValidator = new UrlValidatorTest("validator tester");
	   System.out.println("Validator main tester.");
	   
	   testValidator.testManualTest();
	   testValidator.testYourFirstPartition();
	   testValidator.testYourSecondPartition();	   
  }
   


}
