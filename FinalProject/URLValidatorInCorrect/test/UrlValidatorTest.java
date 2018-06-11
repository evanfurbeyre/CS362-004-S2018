

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
	   
	   System.out.println("http://www.google.com/a/b Valid? " + validator.isValid("http://www.google.com/a/b"));
	   System.out.println("http://www.amazon.com Valid? " + validator.isValid("http://www.amazon.com"));
	   System.out.println("http://www.amazon.co Valid? " + validator.isValid("http://www.amazon.co"));
	   System.out.println("http://www.amazon.cm Valid? " + validator.isValid("http://www.amazon.cm"));
	   System.out.println("http://www.google.com Valid? " + validator.isValid("http://www.google.com"));
	   System.out.println("file://C:/Users/admin/Document Valid? " + validator.isValid("file://C:/Users/admin/Document"));
	   System.out.println("ftp://ftp.test/filefolder/somethinng.txt Valid? " + validator.isValid("ftp://ftp.test/filefolder/somethinng.txt"));
	   System.out.println("sometext Valid? " + validator.isValid("sometext"));
	   System.out.println("http://www.text.net# Valid? " + validator.isValid("http://www.text.net#"));
	   System.out.println();
   }
   
   
   public void testYourFirstPartition()
   {
	   System.out.println("Invalid Schemes, first partition:");
	   System.out.println();
	   
	   UrlValidator validator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
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
						   
						   temp = invalidSchemes[i] + validAuthorities[j] + validPorts[k] + validPaths[l] + validQueries[m];
						   System.out.println(temp + " is " + validator.isValid(temp));
						   System.out.println();
					   }
				   }
			   }
		   }
	   }
   }
   
   public void testYourSecondPartition()
   {
	   System.out.println("Invalid Authorities, second partition:");
	   System.out.println();
	   
	   UrlValidator validator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
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
						   
						   temp = validSchemes[i] + invalidAuthorities[j] + validPorts[k] + validPaths[l] + validQueries[m];
						   System.out.println(temp + " is " + validator.isValid(temp));
						   System.out.println();
					   }
				   }
			   }
		   }
	   }
   }
   
   public void testYourThirdPartition()
   {
	   System.out.println("Invalid Ports, third partition:");
	   System.out.println();
	   
	   UrlValidator validator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
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
						   
						   temp = validSchemes[i] + validAuthorities[j] + invalidPorts[k] + validPaths[l] + validQueries[m];
						   System.out.println(temp + " is " + validator.isValid(temp));
						   System.out.println();
					   }
				   }
			   }
		   }
	   }
   }
   
   public void testYourFourthPartition()
   {
	   System.out.println("Invalid Paths, fourth partition:");
	   System.out.println();
	   
	   UrlValidator validator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
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
						   
						   temp = validSchemes[i] + validAuthorities[j] + validPorts[k] + invalidPaths[l] + validQueries[m];
						   System.out.println(temp + " is " + validator.isValid(temp));
						   System.out.println();
					   }
				   }
			   }
		   }
	   }
   }
   
   public void testYourFifthPartition()
   {
	   System.out.println("Invalid Queries, fifth partition:");
	   System.out.println();
	   
	   UrlValidator validator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
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
						   
						   temp = validSchemes[i] + validAuthorities[j] + validPorts[k] + validPaths[l] + invalidQueries[m];
						   System.out.println(temp + " is " + validator.isValid(temp));
						   System.out.println();
					   }
				   }
			   }
		   }
	   }
   }
   
   //You need to create more test cases for your Partitions if you need to 
   
   public void partitionTester(Object[] tests, int testChoice)
   {
	   UrlValidator validator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
   
	   String[] validSchemes = (String[]) tests[0];
	   String[] invalidSchemes = (String[]) tests[1];
	   String[] validAuthorities = (String[]) tests[2];
	   String[] invalidAuthorities = (String[]) tests[3];
	   String[] validPorts = (String[]) tests[4];
	   String[] invalidPorts = (String[]) tests[5];
	   String[] validPaths = (String[]) tests[6];
	   String[] invalidPaths = (String[]) tests[7];
	   String[] validQueries = (String[]) tests[8];
	   String[] invalidQueries = (String[]) tests[9];
	   
	   String temp;
	   
	   if(testChoice == 0)
	   {
		   System.out.println("All Valid Inputs, expecation is valid/true:");
		   System.out.println();
		   
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
							   
							   temp = validSchemes[i] + validAuthorities[j] + validPorts[k] + validPaths[l] + validQueries[m];
							   System.out.println(temp + " is " + validator.isValid(temp));
							   System.out.println();
						   }
					   }
				   }
			   }
		   }
	   }
	   else if(testChoice == 1)
	   {
		   testYourFirstPartition();
	   }
	   else if(testChoice == 2)
	   {
		   testYourSecondPartition();
	   }
	   else if(testChoice == 3)
	   {
		   testYourThirdPartition();		   
	   }
	   else if(testChoice == 4)
	   {
		   testYourFourthPartition();
	   }
	   else if(testChoice == 5)
	   {
		   testYourFifthPartition();
	   }
	   else
	   {
		   System.out.println("ALL INVALID, expecation is invalid/false:");
		   System.out.println();
		   
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
							   
							   temp = invalidSchemes[i] + invalidAuthorities[j] + invalidPorts[k] + invalidPaths[l] + invalidQueries[m];
							   System.out.println(temp + " is " + validator.isValid(temp));
							   System.out.println();
						   }
					   }
				   }
			   }
		   }
	   }
	   
   }
   
   static String[] validSchemes = {
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
   
   static String[] invalidSchemes = {
		   "9http://",
		   "://",
		   "http#://",
		   "http:",
		   "http:/",
		   "http/",
		   "http//",
		   "ftp:",
		   "ftp@://",
		   ".http://",
   };
   
   static String[] validAuthorities = {
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
   
   static String[] invalidAuthorities = {
		   "www.google.",
		   "google.",
		   "google",
		   "www.google.zz",
		   "google+.com",
		   "255.255.256.255",
		   "255.255.255",
		   "255.255",
		   "255.255.255.255.255",
		   ""
   };
   
   static String[] validPorts = {
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
   
   static String[] invalidPorts = {
		   ":123456",
		   ":1234h",
		   ":p20",
		   ":",
		   "222",
		   ":30&4",
		   "2:0033",
		   ":-33",
		   ":30:80",
		   "::80"
   };
   
   static String[] validPaths = {
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
   
   static String[] invalidPaths = {
		   "something",
		   "path/",
		   "/path#",
		   "/../destination",
		   "/..",
		   "//path",
		   "///path",
		   "//path/",
		   "/<destination>",
		   "/..destination/"
   };
   
   static String[] validQueries = {
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
   
   static String[] invalidQueries = {
		   "mode=readwrite",
		   "?mode#hashtag",
		   "?#",
		   "query",
		   "mode=writeread",
		   "?mode#hashtag",
		   "?#",
		   "?mode75#",
		   "?mode33#",
		   "something"
   };
   
  static Object[] tests = {
		  validSchemes,
		  invalidSchemes,
		  validAuthorities,
		  validAuthorities,
		  validPorts,
		  invalidPorts,
		  validPaths,
		  invalidPaths,
		  validQueries,
		  invalidQueries
  };
  
  public static void main(String[] argv) {

	   UrlValidatorTest testValidator = new UrlValidatorTest("validator tester");
	   System.out.println("Validator main tester.");
	   
	   testValidator.testManualTest();
	  
	   testValidator.partitionTester(tests, 0); //All Valid information
	   testValidator.partitionTester(tests, 1); //Partition 1
	   testValidator.partitionTester(tests, 2); //Partition 2
	   testValidator.partitionTester(tests, 3); //Partition 3
	   testValidator.partitionTester(tests, 4); //Partition 4
	   testValidator.partitionTester(tests, 5); //Partition 5
	   testValidator.partitionTester(tests, 6); //Partition 6
	   
  }
   


}