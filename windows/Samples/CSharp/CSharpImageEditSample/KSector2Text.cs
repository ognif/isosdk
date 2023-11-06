using System;
using System.Collections.Generic;
using System.Text;

namespace Sector2Text
{
    class IsPrintableTranslator
	{
        private const int alphaLower = (int)('A');
        private const int alphaUpper = (int)('z');
        private const int numberLower = (int)('0');
        private const int numberUpper = (int)('9');

        public IsPrintableTranslator()
        {
        }

	    public static String Translate(List<byte> vBytes)
        {
	        String res = new string ('.', vBytes.Count);
            char[] array = res.ToCharArray();

	        for(int i = 0 ; i < (int)vBytes.Count; ++i)
	        {
		        if (alphaLower <= vBytes[i] && vBytes[i] <= alphaUpper)
		        {
                    array[i] = (char)vBytes[i];
		        }
		        else if(numberLower <= vBytes[i] && vBytes[i] <= numberUpper)
		        {
                    array[i] = (char)vBytes[i];
		        }
	        }

	        return new String(array);
        }
	};

    
    class SixteenByteLine
	{
	    private List<byte> m_vBytes = new List<byte> ();
	
		///Reads 16 bytes from pointer. You should now, that pointer s not corrupted;
		public SixteenByteLine()
        {            
        }
        
		public SixteenByteLine(byte[] pData)		
		{
			setData(pData);
		}

        public void setData(byte[] pData)
		{
            m_vBytes.Clear();
            
            for (int i = 0; i < 16; ++i)
            {
                m_vBytes.Add(pData[i]);
            }
		}

        public String getByteString()
		{
			String res = "";			
			
            for(int i = 0 ; i < 16; ++i)
			{
				res += byteToString(m_vBytes[i]);
				
                if (i < 15)
				{		
					if (i == 7)
					{
						res += "   " ;
					}
					else
					{
						res += ' ' ;
					}
				}
			}

			return res;
		}

        public String getHumanReadableString()
        {   
             return IsPrintableTranslator.Translate(m_vBytes);
		}

        //Writes out something like 15 -> 0F
	    private String byteToString(byte nByte)
        {
            String temp = String.Format("{0:X}", nByte);
            temp = temp.PadLeft(2, '0');

            return temp;
        }

	};//class SixteenByteLine


    class SectorLines
	{
	    private List<SixteenByteLine> m_vLines = 
            new List<SixteenByteLine>();
	
		public SectorLines()
		{
			m_vLines.Clear();
		}

		public SectorLines(byte[] pData, uint nSizeOfDataInBytes)
		{
			setData(pData, nSizeOfDataInBytes);			
		}

		public void setData(byte[] pData, uint nSizeOfDataInBytes)
		{
			int n = (int)(nSizeOfDataInBytes / 16);
			
            m_vLines.Clear();

            byte[] pNewData = new byte[16];

			for (int i = 0 ; i < n; ++i)
			{
                m_vLines.Add(new SixteenByteLine());
                Array.Copy(pData, 16 * i, pNewData, 0, 16);
                m_vLines[i].setData(pNewData);
			}

			if ((nSizeOfDataInBytes % 16) != 0)
			{
				SixteenByteLine cAdditionalLine = 
                    new SixteenByteLine();
                				
                Array.Copy(pNewData, 0, pData, 16 * n, nSizeOfDataInBytes % 16);
				
				cAdditionalLine.setData(pNewData);
				
				m_vLines.Add(cAdditionalLine);
			}
		}

		public List<String> getLines()
		{
			List<String> vRes = new List<string>();
			
			for(int i = 0; i < m_vLines.Count; ++i)
			{//LBA
                
                vRes.Add(int16To4Symbols((Int16)(i * 16)) + "  :  "
					+ m_vLines[i].getByteString() + "   "
                    + m_vLines[i].getHumanReadableString());
			}
			return vRes;
		}

        //Writes out something like 31 -> 001F
	    private String int16To4Symbols(Int16 n)
        {
            String temp = String.Format("{0:X}", n);
            temp = temp.PadLeft(4, '0');

            return temp;
        }
	};
}
