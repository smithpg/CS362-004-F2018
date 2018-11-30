

import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!


class TestPartGroup {
	public String[] parts;
	public int invalidStartIndex;
	
	public TestPartGroup(String[] validParts, String[] invalidParts) {
		
		this.parts = new String[validParts.length + invalidParts.length];
		for (int i = 0; i < validParts.length; i++) {
	            parts[i] = validParts[i];
	        }
        for (int i = 0; i < invalidParts.length; i++) {
            parts[validParts.length + i] = invalidParts[i];
        }
		
		this.invalidStartIndex = validParts.length;
	}
	
	public boolean partIsValid(int index) {
		return index < invalidStartIndex;
	}
}

public class UrlValidatorTest extends TestCase {
	

   public UrlValidatorTest(String testName) {
      super(testName);
   }  
   
   public void testManualTest()
   {
	   UrlValidator testValidator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	  
	   // Test arbitrary valid URLs
	   assertTrue(testValidator.isValid("ftp://www.youtube.com/watch?v=J8sWPjYe1tw"));
	   assertTrue(testValidator.isValid("http://google.com"));
	   assertTrue(testValidator.isValid("reddit.com"));
	   
	   // Test arbitrary invalid URLs
	   assertFalse(testValidator.isValid("%^0://google.123"));
	   assertFalse(testValidator.isValid("http:/www.reddit.cm"));
	   assertFalse(testValidator.isValid("www.google"));
   }
   
   
   public void testYourFirstPartition()
   {
	 //You can use this function to implement your First Partition testing	   
	   UrlValidator testURL = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   //all return true
	   String[] validInputPartitionScheme = {"http://www.google.com", 
			   "ftp://www.foo.com",
			   "http://www.bar.com",
			   "http://www.foobar.com",
			   "http://www.osu.com"};
	   boolean res = false;
	   for(int i = 0; i < validInputPartitionScheme.length; i++)
	   {
		   try {res = testURL.isValid(validInputPartitionScheme[i]);}
		   catch(Error e)
		   {System.out.println(validInputPartitionScheme[i]+" caused "+e);} 
	       System.out.println(validInputPartitionScheme[i]+" returned "+res); 
	   }
	   //all return false
	   String[] validInputPartitionNoScheme = {"www.google.com", 
			   "www.foo.com",
			   "www.bar.com",
			   "www.foobar.com",
			   "www.osu.com"};
	   res = false;
	   for(int i = 0; i < validInputPartitionNoScheme.length; i++)
	   {
		   try {res = testURL.isValid(validInputPartitionNoScheme[i]);}
		   catch(Error e)
		   {System.out.println(validInputPartitionNoScheme[i]+" caused "+e);} 
	       System.out.println(validInputPartitionNoScheme[i]+" returned "+res); 
	   }
	   
       
   }
   
   public void testYourSecondPartition(){
		 //You can use this function to implement your Second Partition testing	
	   UrlValidator testURL = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   //these all return true
	   String[] invalidInputPartitionScheme = {"http://www..com", 
			   "http://www.com",
			   "http://www.bar.com.com",
			   "http://ww.foobar.com",
			   "http://www.osu."};
	   boolean res = false;
	   for(int i = 0; i < invalidInputPartitionScheme.length; i++)
	   {
		   try {res = testURL.isValid(invalidInputPartitionScheme[i]);}
		   catch(Error e)
		   {System.out.println(invalidInputPartitionScheme[i]+" caused "+e);} 
	       System.out.println(invalidInputPartitionScheme[i]+" returned "+res); 
	   }
	   //these all return false
	   String[] invalidInputPartitionNoScheme = {"www..com", 
			   "www.com",
			   "www.bar.com.com",
			   "ww.foobar.com",
			   "www.osu."};
	   res = false;
	   for(int i = 0; i < invalidInputPartitionNoScheme.length; i++)
	   {
		   try {res = testURL.isValid(invalidInputPartitionNoScheme[i]);}
		   catch(Error e)
		   {System.out.println(invalidInputPartitionNoScheme[i]+" caused "+e);} 
	       System.out.println(invalidInputPartitionNoScheme[i]+" returned "+res); 
	   }

   }
   
   public void testIsValid()
   {
	   System.out.println("start");
	   UrlValidator testValidator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   boolean res = false;
	   boolean expected = true;
	   do {
		   StringBuilder urlBuffer = new StringBuilder();
		   
		   // Build a URL to test
		   for (int i = 0; i < testParts.length; i++) {
			   
			   expected &= testParts[i].partIsValid(TestPartsIndices[i]);
			   urlBuffer.append(testParts[i].parts[TestPartsIndices[i]]);
		   }
		   
		   // Pass the URL to isValid, and check output against expected result
		   
		   String url = urlBuffer.toString();
//		   System.out.println(url); 
		   
		   System.out.println();
		   try {
			   res = testValidator.isValid(url);
			   assertEquals(expected, res);
		   }
		   catch(Error e)
		   {
			   System.out.println(url + " caused " +e);
		   } 
	       System.out.println(url + " returned " + res); 
	       System.out.println();
		   
		   
	   } while (incrementTestPartsIndices(TestPartsIndices, testParts));
	   
	   
	   
	   
   }
    
   static boolean incrementTestPartsIndices(int[] TestPartsIndices, TestPartGroup[] testParts) {
	      /* Based on function of the same name from UrlValidatorCorrect/test  */
	   
	   	  boolean carry = true;  //add 1 to lowest order part.
	      boolean maxIndex = true;
	      for (int TestPartsIndicesIndex = 0; TestPartsIndicesIndex < TestPartsIndices.length; ++TestPartsIndicesIndex) {
	         int partsArrayIndex = TestPartsIndices[TestPartsIndicesIndex];
	         String[] partsArray = testParts[TestPartsIndicesIndex].parts;
	         if (carry) {
	            if (partsArrayIndex < partsArray.length - 1) {
	            	partsArrayIndex++;
	               TestPartsIndices[TestPartsIndicesIndex] = partsArrayIndex;
	               carry = false;
	            } else {
	               TestPartsIndices[TestPartsIndicesIndex] = 0;
	               carry = true;
	            }
	         }
	         maxIndex &= (partsArrayIndex == (partsArray.length - 1));
	      }


	      return (!maxIndex);
   }
   
   String[] validSchemes = {"http://", "ftp://", "h3t://", ""};
   String[] invalidSchemes = {"http:/", "drf://", "ab^:"};
   TestPartGroup testSchemes = new TestPartGroup(validSchemes, invalidSchemes);
   
   String[] validAuthorities = {"www.google.com", "reddit.com", "www.abc.com", "berkeley.edu"};
   String[] invalidAuthorities = {".abc", "1.2.3", ";lkjf"};
   TestPartGroup testAuthorities = new TestPartGroup(validAuthorities, invalidAuthorities);
   
   String[] validPaths = {"/file", "/file/otherfile", "/drek", ""};
   String[] invalidPaths = {"//ds/", "###//", "/../.."};
   TestPartGroup testPaths = new TestPartGroup(validPaths, invalidPaths);
   
   String[] validQueries = {"?query=thing", "?query=thing&otherquery=otherthing", ""};
   String[] invalidQueries = {"??query&query", "?query=thingotherquery=otherthing", "ab^:"};
   TestPartGroup testQueries = new TestPartGroup(validQueries, invalidQueries);
   
   TestPartGroup[] testParts = {testSchemes, testAuthorities, testPaths, testQueries};
   int[] TestPartsIndices = {0, 0, 0, 0};
}


