#include "stdafx.h"

// ��Ʈ���� ���¸� �����ϴ� 4���� �÷���
// goodbit, badbit, failbit, eofbit
// Ÿ�Կ� ���� �ʴ� ���� ������ failbit �� ������ ���۸� ����ä ����

int main()
{
	std::cout << "��Ʈ�� �÷��� ��Ʈ\n";
	int t;
	std::cout << "���ڸ� �Է��Ͻÿ� : (-1 �Է� �� ������) ";
	while (std::cin >> t){
		std::cout << "�Է� : " << t << std::endl;
		if (-1 == t) 
			break;
	}
	// failbit, badbit �� �Ѵ� off �϶��� null �����͸� ����
	// ���� cin �� ���ڸ� �Է��ϸ� failbit�� Ű�� cin�� ����
	// ���� null �����Ͱ� ���ϵǰ� �̰��� while ���� ���ǹ��� ���Ƿ�
	// ���ڸ� �Է��ϸ� ���������� ��


	std::cout << "\n\n��Ʈ�� �÷��� ��Ʈ �ʱ�ȭ �� ���� ����\n";
	t = 0;
	while (true) {
		std::cout << "���ڸ� �Է��Ͻÿ� : (-1 �Է� �� ������) ";
		std::cin >> t;
		std::cout << "�Է� : (-1 �Է½� ������) " << t << std::endl;
		if (std::cin.fail()) {
			std::cout << "����� �Է��ϼ���\n";
			std::cin.clear();
			std::cin.ignore(100, '\n');
		}
		if (-1 == t)
			break;
	}
	// fail �Լ��� failbit, badbit �� true�� true ����
	// cin.clear() �� �÷��׵� �ʱ�ȭ
	// cin.ignore(int, char) �� int��ŭ, char�� ���ö����� ���� ����

	std::cout << "\n\n���� �÷��׿� ������\n";
	t = 0;
	while (true) {
		std::cout << "���ڸ� �Է��Ͻÿ� : (-1 �Է� �� ������) ";
		//std::cin.setf(std::ios_base::hex, std::ios_base::basefield);		// ���� �÷���
		//std::cin >> t;
		std::cin >> std::hex >> t;		// ������
		std::cout << "�Է� : (-1 �Է½� ������) " << t << std::endl;
		if (std::cin.fail()) {
			std::cout << "����� �Է����ּ���\n";
			std::cin.clear();
			std::cin.ignore(100, '\n');
		}
		if (-1 == t)
			break;
	}
	// �����÷��׷� ó��
	// cin.setf(ios_base::fmtflags, ios_base::fmtflags) ��
	// 2��°���ڴ� x���� ó���� �ʱ�ȭ�ϰ�, ù��° ���ڷ� ���� ���� ���·� ó���϶�� ��
	// ������ basefield �� ������ ó���ϴ� ����� �ʱ�ȭ�ϰ�, hex(16����) �� ó���϶�� ����
	// std::ios_base::hex �� ���� �÷��� (��)

	// �����ڷ� ó��
	// std::cin >> std::hex >> t ���� std::hex�� �̿���
	// cin ���� ���� �޴� ����� ��ȯ 
	// std::hex �� ������(�Լ�)

	// std::endl �� '\n' ��� + std::flush()
	// ��ĭ ���� ���ۿ� �ִ� �����͸� �ٷ� ���


	std::cout << "\n\n��Ʈ�� ����" << std::endl;
	std::cout << "���ڿ��� �Է��Ͻÿ� : (-1 �Է� �� ������) ";

	std::string s;
	std::cin >> s;
	char peek = std::cin.rdbuf()->snextc();	// ��Ʈ�� ��ġ �����ڸ� ��ĭ �����ϰ� ����
											// ��ġ �����ڸ� ���������� ����
	if (std::cin.fail())
		std::cout << "Failed";
	std::cout << "�� ��° �ܾ� �� �ձ��� : " << peek << std::endl;
	std::cin >> s;
	std::cout << "�ٽ� ������ : " << s << std::endl;
}