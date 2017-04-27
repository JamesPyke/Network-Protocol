using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Client
{
    public partial class FrmConnect : Form
    {

        public FrmConnect()
        {
            InitializeComponent();
        }

        private void BtnConnect_Click(object sender, EventArgs e)
        {
            try
            {
                string hostname = TxtHostname.Text;
                Int32 port = Convert.ToInt32(NmuPort.Value);

                TcpClient tcpClient = new TcpClient(hostname, port);

                FrmMain frmMain = new FrmMain(tcpClient);
                frmMain.Show();

                Hide();
            }
            catch (SocketException)
            {
                MessageBox.Show("Error: Connection Failed!", Text, MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

    }
}
