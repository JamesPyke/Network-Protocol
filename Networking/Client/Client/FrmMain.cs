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
    public partial class FrmMain : Form
    {
        private TcpClient tcpClient;
        private NetworkStream networkStream;

        public FrmMain(TcpClient tcpClient)
        {
            InitializeComponent();
            Initialize(tcpClient);
        }

        private void Initialize(TcpClient tcpClient)
        {
            this.tcpClient = tcpClient;
            networkStream = this.tcpClient.GetStream();
            TmrProcessMessages.Enabled = true;
        }

        private void TxtMessage_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode != Keys.Enter || TxtMessage.Text == string.Empty)
                return;

            try
            {
                Byte[] packet = Encoding.ASCII.GetBytes(TxtMessage.Text);
                networkStream.Write(packet, 0, packet.Length);
                TxtMessage.Clear();
            }
            catch (System.IO.IOException)
            {
                MessageBox.Show("Disconnected From Server", Text, MessageBoxButtons.OK, MessageBoxIcon.Error);
                Application.Exit();
            }
        }

        private void TmrProcessMessages_Tick(object sender, EventArgs e)
        {
            if(!networkStream.DataAvailable)
                return;

            Byte[] packet = new Byte[256];     
            Int32 bytesRead = networkStream.Read(packet, 0, packet.Length);

            string message = Encoding.ASCII.GetString(packet, 0, bytesRead);

            if (TxtFeed.Text != string.Empty)
                message = Environment.NewLine + message;

            TxtFeed.AppendText(message);
        }

        private void FrmMain_FormClosed(object sender, FormClosedEventArgs e)
        {
            networkStream.Close();
            tcpClient.Close();

            Application.Exit();
        }
    }
}
